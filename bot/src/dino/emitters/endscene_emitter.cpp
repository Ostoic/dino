#include "endscene_emitter.hpp"

#include "../events/endscene_events.hpp"
#include "../wow/graphics.hpp"
#include "../settings.hpp"
#include "../session.hpp"
#include "../version.hpp"
#include "../log.hpp"
#include "../wow/data/CDataStore.hpp"

#include <chrono>
#include <obfuscator.hpp>

namespace dino::emitters
{
	//namespace
	//{
	//	__declspec(naked) void send_packet_prehook(void* this_, wow::data::CDataStore* data)
	//	{
	//		__asm {
	//			pushad;
	//			pushfd;
	//		}

	//		[&] {
	//			log::debug(OBFUSCATE("[send_packet_prehook] sending packet of size {}"), data->m_size);
	//		}();
	//		
	//		__asm {
	//			popfd;
	//			popad;
	//		}

	//		deref_as<fn_ptr<void
	//	}
	//}

	void endscene_emitter::install()
	{
		auto& emitter = endscene_emitter::get();
		if (emitter.is_active())
			return;

		emitter.hook();

		if (!emitter.is_active())
			log::info(OBFUSCATE("[endscene_emitter::install] unable to install hook"));
		else
			log::info(OBFUSCATE("[endscene_emitter::install] successfully hooked"));
	}

	void endscene_emitter::uninstall()
	{
		auto& emitter = endscene_emitter::get();
		if (emitter.is_active())
			emitter.unhook();
	}

	bool endscene_emitter::is_active() const
	{
		const auto current_endscene_ptr = address{deref_as<address::address_type>(wow::graphics::get_ptr_address())};
		return current_endscene_ptr != endscene_emitter::get().original_endscene();
	}

	address endscene_emitter::original_endscene() const noexcept
	{
		return original_endscene_;
	}

	std::chrono::nanoseconds endscene_emitter::last_hook_runtime() const
	{
		return last_hook_runtime_;
	}

	__declspec(naked) void endscene_hook()
	{
		using clock = std::chrono::high_resolution_clock;
		using namespace std::chrono_literals;

		static address::address_type original_endscene = static_cast<address::address_type>(endscene_emitter::get().original_endscene());


		// Save asm flags
		_asm
		{
			pushad
			pushfd
		}

		[] {
			static auto last_frame_time = clock::now();

			const auto frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>
				(clock::now() - last_frame_time);

			if (frame_duration < dino::session::settings().lookup<std::chrono::milliseconds>("refresh_rate"))
				return;

			last_frame_time = clock::now();

			try
			{
				const auto start = clock::now();
				scheduler::trigger(events::endscene_frame{frame_duration});
				scheduler::update();

				const auto end = clock::now();
				endscene_emitter::get().last_hook_runtime_ = (end - start);
			}
			catch (const std::exception& e)
			{
				log::critical(OBFUSCATE("[endscene_emitter] Exception: {}"), e.what());
			}
		}();

		// Restore any asm flags.
		_asm
		{
			popfd
			popad
			jmp original_endscene;
		};
	}

	endscene_emitter::endscene_emitter()
	{
		original_endscene_ = deref_as<address::address_type>(wow::graphics::get_ptr_address());
	}

	void endscene_emitter::hook()
	{
		auto& endscene_ptr = deref_as<fn_ptr<void()>>(wow::graphics::get_ptr_address());
		endscene_ptr = endscene_hook;
	}

	void endscene_emitter::unhook()
	{
		auto& endscene_ptr = deref_as<fn_ptr<void()>>(wow::graphics::get_ptr_address());
		endscene_ptr
			= fn_ptr<void()>(static_cast<address::address_type>(endscene_emitter::get().original_endscene()));
	}

	endscene_emitter& endscene_emitter::get() noexcept
	{
		static endscene_emitter s_;
		return s_;
	}
}