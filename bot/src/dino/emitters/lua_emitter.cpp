#include "lua_emitter.hpp"

#include "../session.hpp"
#include "../settings.hpp"

#include "../wow/lua.hpp"
#include "../events/dino_events.hpp"
#include "../events/framexml/player_events.hpp"

#include "../script/core.hpp"
#include "../log.hpp"

#include <nlohmann/json.hpp>
#include <obfuscator.hpp>

using json = nlohmann::json;

namespace dino::emitters
{
	namespace
	{
		void check_lua_handler(const events::endscene_frame& event)
		{
			const auto action = wow::lua::last_action();

			if (!action.is_valid())
				return;

			log::info(OBFUSCATE("[check_lua_handler] {}: {}"), action.name(), action.data());
			if (action.name() == OBFUSCATE("lua.execute"))
				wow::lua::execute(action.data());

			else if (action.name() == OBFUSCATE("dino.command"))
			{
				log::info("dino.command: {}", action.data());
				//dino::session::get().dispatcher()
					//.enqueue<events::new_dino_command>(events::new_dino_command{action.data()});
			}

			else if (action.name() == OBFUSCATE("event.emit"))
			{
				const auto json = json::parse(action.data());
				const auto event = wow::framexml::to_event(json["event"]);
				auto& dispatcher = dino::session::get().dispatcher();

				if (event == wow::framexml::event::player_target_changed)
					dispatcher.enqueue<events::framexml::player_target_changed>();

				else if (event == wow::framexml::event::player_entering_world)
					dispatcher.enqueue<events::framexml::player_entering_world>();
			}
		}
	}

	void lua_emitter::install()
	{
		try
		{
			dino::session::get().dispatcher()
				.sink<events::endscene_frame>()
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
		dino::session::get().dispatcher()
			.sink<events::endscene_frame>()
			.disconnect<check_lua_handler>();

		log::info(OBFUSCATE("[lua_emitter] uninstalled"));
	}
}