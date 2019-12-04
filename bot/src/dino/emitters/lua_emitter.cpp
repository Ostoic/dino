#include "lua_emitter.hpp"

#include "../session.hpp"
#include "../settings.hpp"

#include "../wow/lua.hpp"
#include "../events/dino_events.hpp"
#include "../events/framexml/player_events.hpp"
#include "../handlers/command_handler.hpp"

#include "../script/core.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace dino::emitters
{
	namespace
	{
		void check_lua_handler(const events::endscene_frame& event)
		{
			const auto action = wow::lua::action{};
			if (action.name() == "lua.execute")
				wow::lua::execute(action.data());

			else if (action.name() == "dino.command")
			{
				auto& dispatcher = dino::session::get().dispatcher();
				dispatcher
					.enqueue<events::new_dino_command>(events::new_dino_command{action.data()});
			}

			else if (action.name() == "event.emit")
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

			script::load(script::json_script);
			script::load(script::emitter_script);
		}
		catch (const std::exception & e)
		{
			spdlog::critical("Exception: {}", e.what());
		}
	}

	void lua_emitter::uninstall()
	{
		dino::session::get().dispatcher()
			.sink<events::endscene_frame>()
			.disconnect<check_lua_handler>();

		wow::lua::run("dino = {{}}");
	}
}