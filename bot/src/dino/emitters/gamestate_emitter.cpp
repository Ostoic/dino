#include "gamestate_emitter.hpp"
#include "net_emitter.hpp"
#include "lua_emitter.hpp"
#include "warden_emitter.hpp"
#include "spellcast_emitter.hpp"
#include "chat_emitter.hpp"
#include "world_emitter.hpp"

#include "../session.hpp"
#include "../wow/lua.hpp"
#include "../log.hpp"

#include "../events/glue_events.hpp"
#include "../events/framexml/player_events.hpp"
#include "../events/framexml/ui_events.hpp"

#include <obfuscator.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace dino::emitters
{
	namespace
	{
		void reinstall_manditory_emitters(const events::gamestate_change& event)
		{
			constexpr auto either_ingame = [](const auto& left, const auto& right)
			{
				return left == wow::glue::screen::ingame || right == wow::glue::screen::ingame;
			};

			if (either_ingame(event.before, event.after) || event.before == event.after)
			{
				log::info(OBFUSCATE("[reinstall_lua_emitter] reinstalling lua_emitter..."));
				emitters::lua_emitter::uninstall();
				emitters::lua_emitter::install();
			}

			//emitters::warden_emitter::install();
			emitters::net_emitter::install();
		}

		void emit_gamestate_change(const wow::glue::screen prev_screen, const wow::glue::screen current_screen)
		{
			if (current_screen == wow::glue::screen::ingame)
				scheduler::enqueue<events::gamestate_change_ingame>({prev_screen, current_screen});

			else if (current_screen == wow::glue::screen::login)
				scheduler::enqueue<events::gamestate_change_login>({prev_screen, current_screen});

			scheduler::enqueue<events::gamestate_change>({prev_screen, current_screen});
		}

		void update_gamestate_change(const wow::glue::screen current_screen)
		{
			if (current_screen == wow::glue::screen::ingame)
				scheduler::update<events::gamestate_change_ingame>();

			else if (current_screen == wow::glue::screen::login)
				scheduler::update<events::gamestate_change_login>();

			scheduler::update<events::gamestate_change>();
		}

		void check_gamestate_check(const events::endscene_frame& event)
		{
			static wow::glue::screen prev_screen = wow::glue::current_screen();
			const auto current_screen = wow::glue::current_screen();

			if (current_screen != prev_screen)
			{
				emit_gamestate_change(prev_screen, current_screen);
				prev_screen = current_screen;
				update_gamestate_change(current_screen);
			}
		}

		void on_ui_error_message(const events::framexml::received_ui_error_message& event)
		{
			auto json = json::parse(event.data);
			log::info(OBFUSCATE("[lua_emitter] [on_ui_error_message] action.data(): {}"), event.data);
		}

		void enter_world(const events::gamestate_change_ingame& event)
		{
			emitters::lua_emitter::emit_on<events::framexml::received_ui_error_message, on_ui_error_message>(
				wow::framexml::event::ui_error_message,
				OBFUSCATE("emit:ui-error")
			);

			emitters::chat_emitter::install();
			emitters::world_emitter::install();
			emitters::spellcast_emitter::install();
		}

		void log_gamestate(const events::gamestate_change& event)
		{
			const auto id = dino::session::identity();
			spdlog::set_pattern(fmt::format("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l]{} %v",
				id.empty() ? ("") : (fmt::format(" [{}]", id))
			));

			log::info(OBFUSCATE("{} -> {}"), to_string(event.before), to_string(event.after));
		}
	}

	void gamestate_emitter::install()
	{
		// Setup gamestate driver
		scheduler::sink<events::endscene_frame>()
			.connect<check_gamestate_check>();

		 //Handle gamestate_change
		scheduler::sink<events::gamestate_change>()
			.connect<reinstall_manditory_emitters>();

		// Handle enter_world
		scheduler::sink<events::gamestate_change_ingame>()
			.connect<enter_world>();

		// Enable gamestate logging
		scheduler::sink<events::gamestate_change>()
			.connect<log_gamestate>();

		const auto screen = wow::glue::current_screen();
		emit_gamestate_change(screen, screen);
	}

	void gamestate_emitter::uninstall()
	{
		// Disconnect gamestate handler
		scheduler::sink<events::endscene_frame>()
			.disconnect<check_gamestate_check>();

		// Disconnect gamestate_change handler
		scheduler::sink<events::gamestate_change>()
			.disconnect<reinstall_manditory_emitters>();

		// Disconnect enter_world handler
		scheduler::sink<events::gamestate_change_ingame>()
			.disconnect<enter_world>();

		// Disable gamestate logging
		scheduler::sink<events::gamestate_change>()
			.disconnect<log_gamestate>();
	}
}