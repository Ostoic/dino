#include "lua_emitter.hpp"

#include "../session.hpp"
#include "../settings.hpp"

#include "../wow/lua.hpp"
#include "../wow/offsets.hpp"
#include "../wow/world/time.hpp"
#include "../events/dino_events.hpp"
#include "../events/framexml/player_events.hpp"
#include "../events/framexml/ui_events.hpp"

#include "../script/core.hpp"
#include "../log.hpp"
#include "../debug.hpp"

#include <nlohmann/json.hpp>
#include <obfuscator.hpp>

using json = nlohmann::json;

namespace dino::emitters
{
	namespace
	{
		void check_lua_handler(const events::endscene_frame& event)
		{
			namespace chrono = std::chrono;

			const auto start = chrono::high_resolution_clock::now();
			try
			{
				const auto action = wow::lua::last_action();

				if (!action.is_valid())
					return;

				if (action.name() == OBFUSCATE("lua.execute"))
					wow::lua::execute(action.data());

				else if (action.name() == OBFUSCATE("dino.command"))
				{
					//const auto json = json::parse(action.data());
					log::info("dino.command: {}", action.data());

					if (action.data() == "dev")
						dino::debug::dev();

					//if (json[])
					//dino::session::get().dispatcher()
						//.enqueue<events::new_dino_command>(events::new_dino_command{action.data()});
				}

				else if (action.name() == OBFUSCATE("event.emit"))
				{
					const auto json = json::parse(action.data());
					const auto event = wow::framexml::to_event(json["event"]);

					log::info(
						OBFUSCATE("[lua_emitter] [check_lua_handler] event: {}, action.data(): {}"),
						to_string(event), action.data()
					);

					if (event == wow::framexml::event::player_target_changed)
						scheduler::trigger<events::framexml::player_target_changed>();

					else if (event == wow::framexml::event::player_entering_world)
						scheduler::trigger<events::framexml::player_entering_world>();

					else if (event == wow::framexml::event::ui_error_message)
						scheduler::trigger(events::framexml::received_ui_error_message{action.data()});
				}
			}
			catch (const std::exception& e)
			{
				log::error("[lua_emitter] Exception occured: {}", e.what());
			}

			const auto end = chrono::high_resolution_clock::now();

			log::info(
				"[lua_emitter::check_lua_handler] runtime: {} us",
				chrono::duration_cast<chrono::microseconds>(end - start).count()
			);

			const auto time = wow::world::get_async_time();
		}
	}

	void lua_emitter::install()
	{
		try
		{
			scheduler::sink<events::endscene_frame>()
				.connect<check_lua_handler>();

			wow::lua::execute(script::json_script.data());
			wow::lua::execute(script::emitter_script.data());
			log::info(OBFUSCATE("[lua_emitter] installed"));
		}
		catch (const std::exception & e)
		{
			log::critical(OBFUSCATE("Exception: {}"), e.what());
		}
	}

	void lua_emitter::uninstall()
	{
		scheduler::sink<events::endscene_frame>()
			.disconnect<check_lua_handler>();

		log::info(OBFUSCATE("[lua_emitter] uninstalled"));
	}
}