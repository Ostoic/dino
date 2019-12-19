#include "spellcast_emitter.hpp"
#include "emitters.hpp"

#include "../log.hpp"
#include "../session.hpp"

#include "../events/spell_events.hpp"
#include "../events/combat_log_events.hpp"

#include "../wow/data/cast_failed_store.hpp"
#include "../wow/data/packed_guid.hpp"
#include "../wow/data/cooldown_cheat_store.hpp"
#include "../wow/data/health_update_store.hpp"
#include "../wow/data/new_world_store.hpp"

#include <obfuscator.hpp>

namespace dino::emitters
{
	namespace
	{
		void log_cast_failed(const events::received_cast_failed& event)
		{
			log::info(
				OBFUSCATE("[spellcast_emitter] [log_cast_failed] spell_id: {}, pending_cast: {}, error: {}"),
				event.store->spell_id(),
				event.store->pending_spell_cast(),
				event.store->error()
			);
		}

		void log_mount_result(const events::received_mount_result& event)
		{
			log::info(
				OBFUSCATE("[spellcast_emitter] [log_mount_result] flags: {}"),
				event.store->flags()
			);
		}

		void log_spell_heal_log(const events::received_spell_heal_log& event)
		{
			const auto source = event.store->pull<wow::data::packed_guid>().unpack();
			const auto target = event.store->pull<wow::data::packed_guid>().unpack();
			const auto spell_id = event.store->pull<unsigned int>();
			const auto amount_healed1 = event.store->pull<unsigned int>();
			const auto amount_healed2 = event.store->pull<unsigned int>();
			const auto v1 = event.store->pull<unsigned int>();

			log::info(
				OBFUSCATE(
					"[spellcast_emitter] [log_spell_heal_log] source: {},"
					"target: {}, spell_id: {}, amount_healed1: {}, amount_healed2: {},"
					"v1: {}"),
				source, target, spell_id, amount_healed1, amount_healed2, v1
			);
			event.store->restore_cursor();
		}

		void log_spell_start(const events::received_spell_start& event)
		{
			const auto caster = event.store->pull<wow::data::packed_guid>().unpack();
			const auto target = event.store->pull<wow::data::packed_guid>().unpack();
			const auto pending_cast = event.store->pull<std::uint8_t>();
			const auto spell_id = event.store->pull<std::uint32_t>();
			const auto cast_flags = event.store->pull<std::uint32_t>();
			const auto tick_count = event.store->pull<std::uint32_t>();
			log::info(
				OBFUSCATE(
					"[spellcast_emitter] [log_spell_start] caster: {},"
					"target: {}, pending: {}, spellid: {}, cast_flags: {},"
					"tick_count: {}"),
				caster, target, pending_cast,
				spell_id, cast_flags,
				tick_count
			);
			event.store->restore_cursor();
		}

		void log_spell_go(const events::received_spell_go& event)
		{
			const auto caster = event.store->pull<wow::data::packed_guid>().unpack();
			const auto target = event.store->pull<wow::data::packed_guid>().unpack();
			const auto pending_cast = event.store->pull<std::uint8_t>();
			const auto spell_id = event.store->pull<std::uint32_t>();
			const auto cast_flags = event.store->pull<std::uint32_t>();
			const auto tick_count = event.store->pull<std::uint32_t>();
			log::info(
				OBFUSCATE(
					"[spellcast_emitter] [log_spell_go] caster: {},"
					"target: {}, pending: {}, spellid: {}, cast_flags: {},"
					"tick_count: {}"),
				caster, target, pending_cast,
				spell_id, cast_flags,
				tick_count
			);
			event.store->restore_cursor();
		}

		void log_spell_failure(const events::received_spell_failure& event)
		{
			const auto caster = event.store->pull<wow::data::packed_guid>().unpack();
			const auto pending_cast = event.store->pull<std::uint8_t>();
			const auto spell_id = event.store->pull<std::uint32_t>();
			const auto flags = event.store->pull<std::uint32_t>();

			log::info(
				OBFUSCATE("[spellcast_emitter] [log_spell_failure] caster: {}, pending_cast: {}, spell_id: {}, flags: {} "),
				caster, pending_cast, spell_id,
				flags
			);
			event.store->restore_cursor();
		}

		void log_spell_cooldown(const events::received_spell_cooldown& event)
		{
			const auto caster = event.store->pull<wow::guid>();
			const auto pending_cast = event.store->pull<std::uint8_t>();
			log::info(
				OBFUSCATE("[spellcast_emitter] [log_spell_cooldown] caster: {}, pending_cast: {}"),
				caster,
				pending_cast
			);
			event.store->restore_cursor();
		}

		template <class Event>
		void queue_event(const wow::data::store& store)
		{
			dispatcher::enqueue(Event{store});
			dispatcher::update<Event>();
		}

		//void handle_combat_log_multiple(const events::received_combat_log_multiple& event)
		//{
		//	auto count = event.store->pull<unsigned int>();
		//	const auto time = event.store->pull<unsigned int>();

		//	log::info(
		//		OBFUSCATE("handle_combat_log_multiple: packet count: {}, time: {}"),
		//		count, time
		//	);

		//	while (count > 0)
		//	{
		//		const auto time_delta = time - event.store->pull<unsigned int>();
		//		const auto opcode = static_cast<wow::net::messages::server>(event.store->pull<unsigned int>());

		//		log::info(
		//			OBFUSCATE("handle_combat_log_multiple packet: {} {}"),
		//			time_delta, static_cast<unsigned int>(opcode)
		//		);

		//		switch (opcode)
		//		{
		//		case wow::net::messages::server::periodic_aura_log:
		//			log::info(OBFUSCATE("periodic_aura_log packet"));
		//			queue_event<events::received_periodic_aura_log>(
		//				wow::data::store{event.store, event.store->cursor()}
		//			);

		//			break;

		//		case wow::net::messages::server::spell_non_melee_damage_log:
		//			log::info(OBFUSCATE("spell_non_melee_damage_log packet"));
		//			queue_event<events::received_spell_non_melee_damage_log>(
		//				wow::data::store{event.store, event.store->cursor()}
		//			);

		//			break;

		//		case wow::net::messages::server::spell_log_execute:
		//			log::info(OBFUSCATE("spell_log_execute packet"));
		//			queue_event<events::received_spell_log_execute>(
		//				wow::data::store{event.store, event.store->cursor()}
		//			);

		//			break;

		//		case wow::net::messages::server::spell_log_miss:
		//			log::info(OBFUSCATE("spell_log_miss packet"));
		//			queue_event<events::received_spell_heal_log>(
		//				wow::data::store{event.store, event.store->cursor()}
		//			);

		//			break;

		//		case wow::net::messages::server::spell_heal_log:
		//			log::info(OBFUSCATE("spell_heal_log packet"));
		//			queue_event<events::received_spell_heal_log>(
		//				wow::data::store{event.store, event.store->cursor()}
		//			);

		//			break;

		//		case wow::net::messages::server::spell_energize_log:
		//			log::info(OBFUSCATE("spell_energize_log packet"));
		//			queue_event<events::received_spell_energize_log>(
		//				wow::data::store{event.store, event.store->cursor()}
		//			);

		//			break;

		//		case wow::net::messages::server::spell_break_log:
		//			log::info(OBFUSCATE("spell_break_log packet"));
		//			queue_event<events::received_spell_break_log>(
		//				wow::data::store{event.store, event.store->cursor()}
		//			);

		//		case wow::net::messages::server::spell_dispell_log:
		//			log::info(OBFUSCATE("spell_dispell_log packet"));
		//			queue_event<events::received_spell_dispell_log>(
		//				wow::data::store{event.store, event.store->cursor()}
		//			);

		//		case wow::net::messages::server::spell_steal_log:
		//			log::info(OBFUSCATE("spell_steal_log packet"));
		//			queue_event<events::received_spell_steal_log>(
		//				wow::data::store{event.store, event.store->cursor()}
		//			);
		//			break;
		//		}

		//		count--;
		//	}

		//	event.store->restore_cursor();
		//}
	}

	void spellcast_emitter::install()
	{
		emitters::make_net_emitter<events::received_cast_failed>();
		//emitters::make_net_emitter<events::received_cooldown_cheat>();
		//emitters::make_net_emitter<events::received_mount_result>();
		emitters::make_net_emitter<events::received_spell_heal_log>();
		//emitters::make_net_emitter<events::received_spell_failure>();
		//emitters::make_net_emitter<events::received_spell_start>();
		//emitters::make_net_emitter<events::received_spell_go>();
		//emitters::make_net_emitter<events::received_spell_cooldown>();

		//dispatcher::
		//	.sink<events::received_combat_log_multiple>()
		//	.connect<handle_combat_log_multiple>();

		// Enable loggers
		dispatcher::sink<events::received_cast_failed>()
			.connect<log_cast_failed>();

		dispatcher::sink<events::received_mount_result>()
			.connect<log_mount_result>();

		dispatcher::sink<events::received_spell_heal_log>()
			.connect<log_spell_heal_log>();

		dispatcher::sink<events::received_spell_start>()
			.connect<log_spell_start>();

		dispatcher::sink<events::received_spell_failure>()
			.connect<log_spell_failure>();

		dispatcher::sink<events::received_spell_go>()
			.connect<log_spell_go>();
		log::info(OBFUSCATE("[spellcast_emitter] installed"));
	}

	void spellcast_emitter::uninstall()
	{
		emitters::restore_net_emitter<events::received_cast_failed>();
		//emitters::restore_net_emitter<events::received_cooldown_cheat>();
		//emitters::restore_net_emitter<events::received_mount_result>();
		emitters::restore_net_emitter<events::received_spell_heal_log>();
		emitters::restore_net_emitter<events::received_spell_failure>();
		emitters::restore_net_emitter<events::received_spell_start>();
		emitters::restore_net_emitter<events::received_spell_go>();
		emitters::restore_net_emitter<events::received_spell_cooldown>();

		//dispatcher::
		//	.sink<events::received_combat_log_multiple>()
		//	.disconnect<handle_combat_log_multiple>();

		dispatcher::sink<events::received_cast_failed>()
			.disconnect<log_cast_failed>();

		dispatcher::sink<events::received_mount_result>()
			.disconnect<log_mount_result>();

		dispatcher::sink<events::received_spell_heal_log>()
			.disconnect<log_spell_heal_log>();

		dispatcher::sink<events::received_spell_start>()
			.disconnect<log_spell_start>();

		dispatcher::sink<events::received_spell_failure>()
			.disconnect<log_spell_failure>();

		dispatcher::sink<events::received_spell_go>()
			.disconnect<log_spell_go>();
		log::info(OBFUSCATE("[spellcast_emitter] uninstalled"));
	}
}