#include "net_emitter.hpp"

#include "../session.hpp"
#include "../log.hpp"
#include "../hook/vmt_hook.hpp"
#include "../events/net_events.hpp"

#include <obfuscator.hpp>

#include <Windows.h>
#include <Winsock.h>

namespace dino::emitters
{
	namespace
	{
		void __fastcall hook_wc_connected(void* self, void*, void* server, int a3, unsigned int tick_count, sockaddr** addr)
		{
			const auto& wc_connected
				= deref_as<void(__fastcall)(void*, void*, void*, unsigned int, int, sockaddr**)>(wow::offsets::net::net_client::wc_connected);

			auto event = events::received_wc_connected{};

			dispatcher::enqueue(event);
			dispatcher::update<decltype(event)>();

			wc_connected(self, nullptr, server, a3, tick_count, addr);
		}

		void __fastcall hook_wc_disconnected(void* self, void*, int a2, int a3, int a4)
		{
			const auto& wc_disconnected
				= deref_as<void(__fastcall)(void*, void*, int, int, int)>(wow::offsets::net::net_client::wc_disconnected);

			auto event = events::received_wc_disconnected{};

			dispatcher::enqueue(event);
			dispatcher::update<decltype(event)>();

			wc_disconnected(self, nullptr, a2, a3, a4);
		}

		void __fastcall hook_handle_data(void* self, void*, int a2, void* data, unsigned int size)
		{
			// signed int __thiscall NetClient::HandleData(net_client *this, int a2, int a3, int a4)
			const auto& handle_data
				= deref_as<int(__fastcall)(void*, void*, int, void*, unsigned int)>(wow::offsets::net::net_client::handle_data_fn);

			void* data_ = data;
			unsigned int size_ = size;
			auto event = events::received_handle_data{};
			event.data = &data_;
			event.size = &size_;

			dispatcher::enqueue(event);
			dispatcher::update<decltype(event)>();

			handle_data(self, nullptr, a2, data_, size_);
		}

		void log_handle_data(const events::received_handle_data& event)
		{
			const auto* data = reinterpret_cast<wow::net::messages::opcode*>(*event.data);
			log::info("[net_emitter] [log_handle_data] opcode: {}, size: {}", to_string(*data), *event.size);
		}

		void log_wc_connected(const events::received_wc_connected& event)
		{
			log::info("[net_emitter] [log_wc_connected]");
		}

		void log_wc_disconnected(const events::received_wc_disconnected& event)
		{
			log::info("[net_emitter] [log_wc_disconnected]");
		}
	}

	void net_emitter::install()
	{
		try
		{
			static auto vmt_hook_cc = std::make_unique<hook::vmt_hook>(
				wow::offsets::net::client_connection::vtable
			);

			static auto vmt_hook_rc = std::make_unique<hook::vmt_hook>(
				wow::offsets::net::realm_connection::vtable
			);

			static auto vmt_hook_nc = std::make_unique<hook::vmt_hook>(
				wow::offsets::net::net_client::vtable
			);

			vmt_hook_cc->hook(2, hook_wc_connected);
			vmt_hook_rc->hook(2, hook_wc_connected);
			vmt_hook_nc->hook(2, hook_wc_connected);

			vmt_hook_cc->hook(4, hook_wc_disconnected);
			vmt_hook_rc->hook(4, hook_wc_disconnected);
			vmt_hook_nc->hook(4, hook_wc_disconnected);

			//vmt_hook_cc->hook(14, hook_handle_data);
			//vmt_hook_rc->hook(14, hook_handle_data);
			//vmt_hook_nc->hook(14, hook_handle_data);

			dispatcher::sink<events::received_handle_data>()
				.connect<log_handle_data>();

			dispatcher::sink<events::received_wc_connected>()
				.connect<log_wc_connected>();

			dispatcher::sink<events::received_wc_disconnected>()
				.connect<log_wc_disconnected>();

			log::info(OBFUSCATE("[net_emitter] installed"));
		}
		catch (const std::exception & e)
		{
			log::critical(OBFUSCATE("[net_emitter] exception: {}"), e.what());
		}
	}

	void net_emitter::uninstall()
	{
		//dispatcher::
		//	.sink<events::endscene_frame>()
		//	.disconnect<check_lua_handler>();

		log::info(OBFUSCATE("[net_emitter] uninstalled"));
	}
}