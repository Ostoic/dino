#include "gamestate_emitter.hpp"

#include "../session.hpp"
#include "../events/glue_events.hpp"

#include "../wow/console.hpp"
#include "../wow/lua.hpp"

#include "../log.hpp"

namespace dino::emitters
{
	namespace
	{
		void emit_gamestate_change(const wow::glue::screen prev_screen, const wow::glue::screen current_screen)
		{
			auto& dispatcher = dino::session::get().dispatcher();
			if (current_screen == wow::glue::screen::ingame)
				dispatcher.enqueue<events::gamestate_change_ingame>({prev_screen, current_screen});

			else if (current_screen == wow::glue::screen::login)
				dispatcher.enqueue<events::gamestate_change_login>({prev_screen, current_screen});

			dispatcher.enqueue<events::gamestate_change>({prev_screen, current_screen});
		}

		void check_gamestate_check(const events::endscene_frame& event)
		{
			static wow::glue::screen prev_screen = wow::glue::current_screen();
			const auto current_screen = wow::glue::current_screen();
			auto& dispatcher = dino::session::get().dispatcher();

			if (current_screen != prev_screen)
			{
				emit_gamestate_change(prev_screen, current_screen);
				prev_screen = current_screen;
				dispatcher.update<events::gamestate_change>();
			}
		}

		void log_gamestate(const events::gamestate_change& event)
		{
			log::info("CURRENT_GLUE_SCREEN: {}", wow::lua::get_text("CURRENT_GLUE_SCREEN"));
			log::info("{} -> {}", to_string(event.before), to_string(event.after));
		}
	}

	void gamestate_emitter::install()
	{
		auto& dispatcher = dino::session::get().dispatcher();

		// Setup gamestate driver
		dispatcher
			.sink<events::endscene_frame>()
			.connect<check_gamestate_check>();

		// Enable gamestate logging
		dispatcher
			.sink<events::gamestate_change>()
			.connect<log_gamestate>();

		const auto screen = wow::glue::current_screen();
		emit_gamestate_change(screen, screen);
	}

	void gamestate_emitter::uninstall()
	{
		dino::session::get().dispatcher()
			.sink<events::endscene_frame>()
			.disconnect<check_gamestate_check>();
	}
}