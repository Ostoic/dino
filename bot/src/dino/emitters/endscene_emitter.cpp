#include "endscene_emitter.hpp"

#include "../wow/console.hpp"
#include "../wow/graphics.hpp"
#include "../settings.hpp"
#include "../session.hpp"
#include "../version.hpp"
#include "../events/endscene_events.hpp"

#include <chrono>

namespace dino::emitters
{
	unsigned int endscene_emitter::original_endscene = static_cast<unsigned int>
		(bind_value(wow::graphics::get_ptr_address()));

	void endscene_emitter::install()
	{
		auto& emitter = endscene_emitter::get();
		if (!emitter.is_active())
			emitter.hook();
	}

	void endscene_emitter::uninstall()
	{
		auto& emitter = endscene_emitter::get();
		if (emitter.is_active())
			emitter.unhook();
	}

	bool endscene_emitter::is_active() const
	{
		return bind_value(wow::graphics::get_ptr_address()) != endscene_emitter::original_endscene;
	}

	__declspec(naked) void endscene_hook()
	{
		using clock = std::chrono::high_resolution_clock;
		using namespace std::chrono_literals;

		static auto original_endscene = endscene_emitter::original_endscene;

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

			if (frame_duration < settings::refresh_rate())
				return;

			last_frame_time = clock::now();
			auto& dispatcher = dino::session::get().dispatcher();
			dispatcher.enqueue(events::endscene_frame{frame_duration});
			dispatcher.update();

			//try
			//{
			//	endscene_emitter.update_session();

			//	// Run services
			//	if (!services.empty())
			//		for (const auto& service : services)
			//			service.fn();

			//	// Run any new tasks
			//	if (!tasks.empty())
			//	{
			//		// This is synchronized since tasks are meant to run once, so it is more likely endscene
			//		// will race with another contending thread.
			//		auto lock = std::unique_lock<std::mutex>{endscene_emitter.tasks_mutex_};
			//		if (lock.owns_lock())
			//		{
			//			while (!tasks.empty())
			//			{
			//				tasks.front()();
			//				tasks.pop();
			//			}
			//		}
			//	}
			//}
			//catch (const std::exception & e)
			//{
			//	wow::console::dino("Error: {}", e.what());
			//}
		}();

		// Restore any asm flags.
		_asm
		{
			popfd
			popad
			jmp original_endscene;
		};
	}

	void endscene_emitter::update_session()
	{
		dino::session::get().update();
	}

	endscene_emitter::endscene_emitter()
	{
		endscene_emitter::original_endscene = deref_as<unsigned int>(wow::graphics::get_ptr_address());
	}

	void endscene_emitter::hook()
	{
		deref_as<fn_ptr<void()>>(wow::graphics::get_ptr_address())
			= endscene_hook;
	}

	void endscene_emitter::unhook()
	{
		// Make endscene_emitter unhook itself
		deref_as<fn_ptr<void()>>(wow::graphics::get_ptr_address())
			= fn_ptr<void()>(static_cast<unsigned int>(endscene_emitter::original_endscene));
	}

	endscene_emitter& endscene_emitter::get() noexcept
	{
		static endscene_emitter s_;
		return s_;
	}
}