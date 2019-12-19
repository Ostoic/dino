#include "warden_emitter.hpp"
#include "emitters.hpp"

#include "../events/warden_events.hpp"
#include "../wow/warden/warden.hpp"
#include "../wow/warden/rc4.hpp"
#include "../wow/lua.hpp"
#include "../session.hpp"
#include "../log.hpp"

#include <obfuscator.hpp>
#include <sstream>

namespace dino::emitters
{
	namespace
	{
		void log_warden_data(const events::received_warden_data& event)
		{
			//const auto size = event.store->size() - event.store->cursor();
			//log::info(OBFUSCATE("[warden_emitter] [log_warden_data] {}"), event.store->pull<const char*>(size));
		}

		void log_warden_loaded(const events::warden_loaded& event)
		{
			log::info(OBFUSCATE("[warden_emitter] [log_warden_loaded] warden_loaded"));
			log::info(OBFUSCATE("[warden_emitter] warden::base = {}"), wow::warden::base());
			log::info(OBFUSCATE("[warden_emitter] warden::scan_fn = {}"), wow::warden::scan_fn());
		}

		void log_warden_send_scan(const events::send_warden_scan& event)
		{
			const auto* scan_results = reinterpret_cast<const byte*>(*event.scan_results);
			const unsigned int scan_size = *event.scan_size;

			const auto bytes
				= std::vector<byte>{scan_results, scan_results + scan_size};

			const auto decrypted
				= wow::warden::rc4::decrypt(bytes, wow::warden::get_key_out());

			log::info(
				OBFUSCATE("[warden_emitter] [log_warden_send_scan] warden_opcode: {}"),
				static_cast<unsigned int>(decrypted[0])
			);

			std::stringstream bytes_string;
			for (const auto byte : decrypted)
				bytes_string << std::hex << "0x" << static_cast<unsigned int>(byte) << ", ";

			log::info(OBFUSCATE("[warden_emitter] [log_warden_send_scan] size: {}, decrypted: {}"),
				scan_size, bytes_string.str()
			);

			log::info(OBFUSCATE("[warden_emitter] [log_warden_send_scan] decrypted-string: {}"),
				(const char*)decrypted.data()
			);
		}

		void check_warden_state(const events::endscene_frame& event)
		{
			static bool was_loaded = false;

			if (wow::warden::is_loaded() != was_loaded)
			{
				// Previously was not loaded, but now is
				if (!was_loaded)
				{
					was_loaded = true;
					dispatcher::enqueue<events::warden_loaded>();
				}
				else
				{
					// Previously was loaded, but now is not
					was_loaded = false;
					dispatcher::enqueue<events::warden_unloaded>();
				}
			}
		}

		void __stdcall send_warden_scan(void* scan_results, unsigned int scan_size)
		{
			const auto& send_scan
				= deref_as<void(__stdcall)(void*, unsigned int)>(wow::offsets::net::messages::packet_cmsg_warden_data_fn);

			bool drop_packet = false;
			auto event = events::send_warden_scan{};
			event.drop_packet = &drop_packet;
			event.scan_results = &scan_results;
			event.scan_size = &scan_size;

			dispatcher::enqueue(event);
			dispatcher::update<decltype(event)>();

			if (drop_packet)
				return;

			send_scan(scan_results, scan_size);
		}
	}

	void warden_emitter::install()
	{
		// Setup warden state driver
		dispatcher::sink<events::endscene_frame>()
			.connect<check_warden_state>();

		//dispatcher::sink<events::received_warden_data>()
		//	.connect<log_warden_data>();

		//dispatcher::sink<events::warden_loaded>()
		//	.connect<log_warden_loaded>();

		//dispatcher::sink<events::send_warden_scan>()
		//	.connect<log_warden_send_scan>();

		emitters::make_net_emitter<events::received_warden_data>();

		auto& fn_ptr = deref_as<void(__stdcall*)(void*, unsigned int)>(wow::offsets::net::messages::cmsg_warden_data_fn_ptr);

		// Hook send_warden_scan function pointer
		DWORD old_flags = 0;
		VirtualProtect(std::addressof(fn_ptr), 4, PAGE_EXECUTE_READWRITE, &old_flags);
		fn_ptr = &send_warden_scan;
		VirtualProtect(std::addressof(fn_ptr), 1, old_flags, &old_flags);
		log::info(OBFUSCATE("[warden_emitter] installed"));
	}

	void warden_emitter::uninstall()
	{
		// Setup warden state driver
		dispatcher::sink<events::endscene_frame>()
			.disconnect<check_warden_state>();

		dispatcher::sink<events::received_warden_data>()
			.disconnect<log_warden_data>();

		dispatcher::sink<events::warden_loaded>()
			.disconnect<log_warden_loaded>();

		dispatcher::sink<events::send_warden_scan>()
			.disconnect<log_warden_send_scan>();

		emitters::restore_net_emitter<events::received_warden_data>();
		auto& fn_ptr = deref_as<void(*)(void*, unsigned int)>(wow::offsets::net::messages::cmsg_warden_data_fn_ptr);

		// Unhook send_warden_scan function pointer
		DWORD old_flags = 0;
		VirtualProtect(std::addressof(fn_ptr), 4, PAGE_EXECUTE_READWRITE, &old_flags);
		fn_ptr = &deref_as<void(void*, unsigned int)>(wow::offsets::net::messages::packet_cmsg_warden_data_fn);
		VirtualProtect(std::addressof(fn_ptr), 1, old_flags, &old_flags);
		log::info(OBFUSCATE("[warden_emitter] uninstalled"));
	}
}