#include "world_emitter.hpp"
#include "emitters.hpp"

#include "../log.hpp"
#include "../session.hpp"
#include "../events/world_events.hpp"
#include "../wow/data/cast_failed_store.hpp"
#include "../wow/data/cooldown_cheat_store.hpp"
#include "../wow/data/health_update_store.hpp"
#include "../wow/data/new_world_store.hpp"
#include "emitters.hpp"

#include <obfuscator.hpp>

namespace dino::emitters
{
	namespace
	{
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

		void log_loot_list(const events::received_loot_list& event)
		{
			const auto looted_guid = event.store->pull<wow::guid>();
			event.store->restore_cursor();
			log::info(
				OBFUSCATE("[world_emitter] log_loot_list: {}"),
				looted_guid
			);
		}

		void log_update_object(const events::received_update_object& event)
		{
			const auto var1 = event.store->pull<unsigned int>();
			const auto var2 = event.store->pull<std::uint8_t>();
			event.store->restore_cursor();
			log::info(
				OBFUSCATE("[world_emitter] log_update_object: {} {}"),
				var1, var2
			);
		}

		void log_stand_state_update(const events::received_stand_state_update& event)
		{
			const auto var = event.store->pull<std::uint8_t>();
			event.store->restore_cursor();
			log::info(
				OBFUSCATE("[world_emitter] log_update_object: {}"),
				var
			);
		}

		void log_notification(const events::received_stand_state_update& event)
		{
			const auto var = event.store->pull<std::string>(0x1000u);
			event.store->restore_cursor();
			log::info(
				OBFUSCATE("[world_emitter] log_notification: {}"),
				var
			);
		}
	}

	void world_emitter::install()
	{
		emitters::make_net_emitter<events::received_new_world>();
		emitters::make_net_emitter<events::received_health_update>();
		emitters::make_net_emitter<events::received_ai_reaction>();
		emitters::make_net_emitter<events::received_loot_list>();
		//emitters::make_net_emitter<events::received_update_object>();
		emitters::make_net_emitter<events::received_stand_state_update>();
		emitters::make_net_emitter<events::received_notification>();

		// Enable loggers
		dino::session::dispatcher()
			.sink<events::received_new_world>()
			.connect<log_new_world>();

		dino::session::dispatcher()
			.sink<events::received_health_update>()
			.connect<log_health_update>();

		dino::session::dispatcher()
			.sink<events::received_ai_reaction>()
			.connect<log_ai_reaction>();

		dino::session::dispatcher()
			.sink<events::received_loot_list>()
			.connect<log_loot_list>();

		dino::session::dispatcher()
			.sink<events::received_update_object>()
			.connect<log_update_object>();

		dino::session::dispatcher()
			.sink<events::received_stand_state_update>()
			.connect<log_stand_state_update>();

		dino::session::dispatcher()
			.sink<events::received_stand_state_update>()
			.connect<log_notification>();

		log::info(OBFUSCATE("[world_emitter] installed world emitters"));
	}

	void world_emitter::uninstall()
	{
		emitters::restore_net_emitter<events::received_new_world>();
		emitters::restore_net_emitter<events::received_health_update>();
		emitters::restore_net_emitter<events::received_ai_reaction>();
		emitters::restore_net_emitter<events::received_loot_list>();
		//emitters::restore_net_emitter<events::received_update_object>();
		emitters::restore_net_emitter<events::received_stand_state_update>();
		emitters::restore_net_emitter<events::received_notification>();

		dino::session::dispatcher()
			.sink<events::received_new_world>()
			.disconnect<log_new_world>();

		dino::session::dispatcher()
			.sink<events::received_health_update>()
			.disconnect<log_health_update>();

		dino::session::dispatcher()
			.sink<events::received_ai_reaction>()
			.disconnect<log_ai_reaction>();

		dino::session::dispatcher()
			.sink<events::received_loot_list>()
			.disconnect<log_loot_list>();

		dino::session::dispatcher()
			.sink<events::received_update_object>()
			.disconnect<log_update_object>();

		dino::session::dispatcher()
			.sink<events::received_stand_state_update>()
			.disconnect<log_stand_state_update>();

		log::info(OBFUSCATE("[world_emitter] uninstalled world emitters"));
	}
}