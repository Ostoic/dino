#include "spellcast_emitter.hpp"

#include "../log.hpp"
#include "../session.hpp"
#include "../events/world_events.hpp"
#include "../wow/data/cast_failed_store.hpp"
#include "../wow/data/cooldown_cheat_store.hpp"
#include "../wow/data/health_update_store.hpp"
#include "../wow/data/new_world_store.hpp"
#include "set_message_handler.hpp"

#include <obfuscator.hpp>

namespace dino::emitters
{
	namespace
	{
		void on_cast_failed(int a1, int a2, int a3, void* cdata)
		{
			auto& dispatcher = dino::session::dispatcher();
			auto original_handler = bind_fn<void(int, int, int, void*)>(
				wow::offsets::net::messages::packet_smsg_cast_failed_fn
			);

			auto event = events::received_cast_failed{wow::data::cast_failed_store{cdata}};

			// Queue received_cast_failed event
			dispatcher.enqueue(std::move(event));

			// Signal received_cast_failed handlers
			dispatcher.update<decltype(event)>();

			original_handler(a1, a2, a3, cdata);
		}
		void on_cooldown_cheat(int a1, int a2, int a3, void* cdata)
		{
			auto& dispatcher = dino::session::dispatcher();
			auto original_handler = bind_fn<void(int, int, int, void*)>(
				wow::offsets::net::messages::packet_smsg_cooldown_cheat_fn
			);

			auto event = events::received_cooldown_cheat{wow::data::cooldown_cheat_store{cdata}};

			// Queue health_update event
			dispatcher.enqueue(std::move(event));

			// Signal health_update handlers
			dispatcher.update<decltype(event)>();

			original_handler(a1, a2, a3, cdata);
		}

		void on_mount_result(int a1, int a2, int a3, void* cdata)
		{
			auto& dispatcher = dino::session::dispatcher();
			auto original_handler = bind_fn<void(int, int, int, void*)>(
				wow::offsets::net::messages::packet_smsg_mount_result_fn
			);

			auto event = events::received_mount_result{wow::data::mount_result_store{cdata}};

			// Queue health_update event
			dispatcher.enqueue(std::move(event));

			// Signal health_update handlers
			dispatcher.update<decltype(event)>();

			original_handler(a1, a2, a3, cdata);
		}

		void log_cast_failed(const events::received_cast_failed& event)
		{
			log::info(
				OBFUSCATE("log_cast_failed: {}, {}, {}"),
				event.store->spell_id(),
				event.store->pending_spell_cast(),
				event.store->error()
			);
		}
		void log_cooldown_cheat(const events::received_cooldown_cheat& event)
		{
			log::info(
				OBFUSCATE("log_cooldown_cheat: {}"),
				event.store->receiver()
			);
		}

		void log_mount_result(const events::received_mount_result& event)
		{
			log::info(
				OBFUSCATE("log_mount_result: {}"),
				event.store->flags()
			);
		}
	}

	void spellcast_emitter::install()
	{
		emitters::set_net_message_handler(
			wow::net::messages::server::cast_failed,
			on_cast_failed
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::cooldown_cheat,
			on_cooldown_cheat
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::mount_result,
			on_mount_result
		);

		// Enable loggers

		dino::session::dispatcher()
			.sink<events::received_cast_failed>()
			.connect<log_cast_failed>();

		dino::session::dispatcher()
			.sink<events::received_cooldown_cheat>()
			.connect<log_cooldown_cheat>();

		dino::session::dispatcher()
			.sink<events::received_mount_result>()
			.connect<log_mount_result>();

		log::info(OBFUSCATE("[spellcast_emitter] installed"));
	}

	void spellcast_emitter::uninstall()
	{
		emitters::set_net_message_handler(
			wow::net::messages::server::cast_failed,
			bind_fn<void(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_cast_failed_fn)
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::cooldown_cheat,
			bind_fn<void(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_cooldown_cheat_fn)
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::mount_result,
			bind_fn<void(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_mount_result_fn)
		);

		dino::session::dispatcher()
			.sink<events::received_cast_failed>()
			.disconnect<log_cast_failed>();

		dino::session::dispatcher()
			.sink<events::received_cooldown_cheat>()
			.disconnect<log_cooldown_cheat>();

		dino::session::dispatcher()
			.sink<events::received_mount_result>()
			.disconnect<log_mount_result>();

		log::info(OBFUSCATE("[spellcast_emitter] uninstalled"));
	}
}