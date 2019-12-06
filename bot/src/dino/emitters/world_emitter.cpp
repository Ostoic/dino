#include "world_emitter.hpp"

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
		void on_new_world(int a1, int a2, int a3, void* cdata)
		{
			auto& dispatcher = dino::session::dispatcher();
			auto original_handler = bind_fn<void(int, int, int, void*)>(
				wow::offsets::net::messages::packet_smsg_new_world_fn
			);

			auto event = events::received_new_world{wow::data::new_world_store{cdata}};

			// Queue received_new_world event
			dispatcher.enqueue(std::move(event));

			// Signal received_new_world handlers
			dispatcher.update<decltype(event)>();

			original_handler(a1, a2, a3, cdata);
		}

		void on_health_update(int a1, int a2, int a3, void* cdata)
		{
			auto& dispatcher = dino::session::dispatcher();
			auto original_handler = bind_fn<void(int, int, int, void*)>(
				wow::offsets::net::messages::packet_smsg_health_update_fn
			);

			auto event = events::received_health_update{wow::data::health_update_store{cdata}};

			// Queue health_update event
			dispatcher.enqueue(std::move(event));

			// Signal health_update handlers
			dispatcher.update<decltype(event)>();

			original_handler(a1, a2, a3, cdata);
		}

		void on_ai_reaction(int a1, int a2, int a3, void* cdata)
		{
			auto& dispatcher = dino::session::dispatcher();
			auto original_handler = bind_fn<void(int, int, int, void*)>(
				wow::offsets::net::messages::packet_smsg_ai_reaction_fn
			);

			auto event = events::received_ai_reaction{wow::data::ai_reaction_store{cdata}};

			// Queue health_update event
			dispatcher.enqueue(std::move(event));

			// Signal health_update handlers
			dispatcher.update<decltype(event)>();

			original_handler(a1, a2, a3, cdata);
		}

		void log_new_world(const events::received_new_world& event)
		{
			log::info(
				OBFUSCATE("[world_emitter] log_new_world: {} ({}, {}, {})"),
				event.store->map_index(),
				event.store->x(),
				event.store->y(),
				event.store->z()
			);
		}

		void log_health_update(const events::received_health_update& event)
		{
			log::info(
				OBFUSCATE("[world_emitter] log_health_update: +{} -> {}"),
				event.store->amount_healed(),
				event.store->receiver()
			);
		}

		void log_ai_reaction(const events::received_ai_reaction& event)
		{
			log::info(
				OBFUSCATE("[world_emitter] log_ai_reaction: {}, {}"),
				event.store->agent(),
				event.store->flags()
			);
		}
	}

	void world_emitter::install()
	{
		emitters::set_net_message_handler(
			wow::net::messages::server::new_world,
			on_new_world
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::health_update,
			on_health_update
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::ai_reaction,
			on_ai_reaction
		);

		// Enable loggers
		dino::session::get().dispatcher()
			.sink<events::received_new_world>()
			.connect<log_new_world>();

		dino::session::get().dispatcher()
			.sink<events::received_health_update>()
			.connect<log_health_update>();

		dino::session::get().dispatcher()
			.sink<events::received_ai_reaction>()
			.connect<log_ai_reaction>();

		log::info(OBFUSCATE("[world_emitter] installed world emitters"));
	}

	void world_emitter::uninstall()
	{
		emitters::set_net_message_handler(
			wow::net::messages::server::new_world,
			bind_fn<void(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_new_world_fn)
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::health_update,
			bind_fn<void(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_health_update_fn)
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::ai_reaction,
			bind_fn<void(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_ai_reaction_fn)
		);

		dino::session::get().dispatcher()
			.sink<events::received_new_world>()
			.disconnect<log_new_world>();

		dino::session::get().dispatcher()
			.sink<events::received_health_update>()
			.disconnect<log_health_update>();

		dino::session::get().dispatcher()
			.sink<events::received_ai_reaction>()
			.disconnect<log_ai_reaction>();

		log::info(OBFUSCATE("[world_emitter] uninstalled world emitters"));
	}
}