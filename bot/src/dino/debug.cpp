#include "debug.hpp"
#include "session.hpp"
#include "dispatcher.hpp"
#include "log.hpp"

#include "wow/lua.hpp"
#include "wow/cvar.hpp"
#include "wow/glue/glue.hpp"
#include "wow/chat/message.hpp"
#include "wow/world/entity_manger.hpp"

#include "events/spell_events.hpp"
#include "events/combat_log_events.hpp"

#include "wow/data/store.hpp"
#include "wow/data/packed_guid.hpp"


#include <obfuscator.hpp>
#include <chrono>

namespace dino::debug
{
	namespace
	{
		void ignore_other_spell_start(const events::received_spell_start& event)
		{
			*event.drop_packet = true;
			//const auto source = event.store->pull<wow::data::packed_guid>().unpack();
			//const auto target = event.store->pull<wow::data::packed_guid>().unpack();

			//const auto local_guid = wow::world::local_guid();
			//if (!(source == local_guid || target == local_guid))
			//	*event.drop_packet = true;
			//event.store->restore_cursor();
		}

		void ignore_other_spell_go(const events::received_spell_go& event)
		{
			*event.drop_packet = true;
			//const auto source = event.store->pull<wow::data::packed_guid>().unpack();
			//const auto target = event.store->pull<wow::data::packed_guid>().unpack();

			//const auto local_guid = wow::world::local_guid();
			//if (!(source == local_guid || target == local_guid))
			//	*event.drop_packet = true;
			//event.store->restore_cursor();
		}

		void ignore_other_spell_heal(const events::received_spell_heal_log& event)
		{
			*event.drop_packet = true;
			//const auto source = event.store->pull<wow::data::packed_guid>().unpack();
			//const auto target = event.store->pull<wow::data::packed_guid>().unpack();

			////const auto local_guid = wow::world::local_guid();
			////if (!(source == local_guid || target == local_guid))
			//*event.drop_packet = true;
			//event.store->restore_cursor();
		}
	}

	void dev()
	{
		//const auto& set_facing = deref_as<int __fastcall(void*, void*, int, int, int, int, char, float, int, std::uint64_t, char)>(
		//	wow::offsets::world::entities::unit::send_movement_packet_fn
		//);

		//log::info("[dev] local_base: {}", static_cast<unsigned int>(wow::world::local_base()));
		log::info("[dev] event list:");

		//for (const auto& event : events)
			//log::info("[dev] event: {}", event);

		//set_facing(
			//(void*)deref_wow::world::local_base(),
		//);

		//const auto realm_list = wow::cvar::lookup("realmList");
		//if (!realm_list.valid())
		//	log::info("[dev] realm_list is invalid");
		//else
		//{
		//	log::info("realm_list: name: {}, value: {}, data: {}, default_value: {}",
		//		realm_list.name(),
		//		realm_list.value(),
		//		realm_list.data(),
		//		realm_list.default_value()
		//	);
		//}
		//session::queue_transient<events::gamestate_change>([](const auto& event)
		//{
		//	log::info("screen: {}", to_string(event.after));
		//	if (event.after == wow::glue::screen::character_select)
		//	{
		//		log::info("character select!");
		//		wow::lua::run(OBFUSCATE("EnterWorld()"));
		//		return handlers::task_handler::transient_state::disconnect;
		//	}

		//	return handlers::task_handler::transient_state::pass;
		//});
	}

	void allocate_console()
	{
		if (::AllocConsole())
		{
			freopen("CONOUT$", "w", stderr);
			freopen("CONOUT$", "w", stdout);
			freopen("CONIN$", "r", stdin);
		}

		log::info(OBFUSCATE("[dino] Console allocated"));
	}

	void delete_console()
	{
		::FreeConsole();
		log::info(OBFUSCATE("[dino] Freed console"));
	}
}