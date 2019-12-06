#include "session.hpp"

#include "wow/console.hpp"
#include "wow/data/message_store.hpp"
#include "version.hpp"
#include "settings.hpp"

#include "emitters/gamestate_emitter.hpp"
#include "emitters/endscene_emitter.hpp"
#include "emitters/world_emitter.hpp"
#include "emitters/spellcast_emitter.hpp"
#include "emitters/chat_emitter.hpp"
#include "emitters/lua_emitter.hpp"

#include "handlers/gamestate_handler.hpp"
#include "events/console_events.hpp"
#include "events/endscene_events.hpp"
#include "events/dino_events.hpp"
#include "events/glue_events.hpp"
#include "events/framexml/player_events.hpp"

#include "hacks/translator.hpp"
#include "hacks/anti_afk.hpp"

#include "wow/glue/glue.hpp"
#include "wow/lua.hpp"

#include "log.hpp"

#include <obfuscator.hpp>

// headers for code-to-rewrite

namespace dino
{
	template <class ChatEvent>
	void log_chat(const ChatEvent& event)
	{
		const auto text = event.store->text();
		const auto sender = event.store->sender();

		log::info(
			OBFUSCATE("[chat_emitter] [{}] [{}]: {}"),
			to_string_view(event.store->msg_type()),
			sender,
			text
		);
	}

	void log_emote(const events::received_text_emote& event)
	{
		log::info(
			OBFUSCATE("[chat_emitter] {} ->text_emote> {}"),
			event.store->sender_guid(),
			event.store->target_name()
		);
	}

	void enter_world(const events::gamestate_change_ingame& event)
	{
		using namespace std::chrono_literals;
		session::queue_async_task(1s, [] {
			log::info(OBFUSCATE("[enter_world] Installing chat_emitter..."));
			emitters::chat_emitter::install();

			log::info(OBFUSCATE("[enter_world] Installing world_emitter..."));
			emitters::world_emitter::install();

			log::info(OBFUSCATE("[enter_world] Installing spellcast_emitter..."));
			emitters::spellcast_emitter::install();
		});
	}

	void session::start()
	{
		try
		{
			settings::internal::initialize();
			wow::console::enable();
			wow::console::open();

			// Setup task handler for .queue_task()
			session::dispatcher()
				.sink<events::endscene_frame>()
				.connect<handlers::task_handler::handle>();

			install_loggers();

			// Handle enter_world
			dispatcher()
				.sink<events::gamestate_change_ingame>()
				.connect<enter_world>();

			dispatcher()
				.sink<events::gamestate_change>()
				.connect<handlers::reinstall_lua_emitter>();

			session::queue_task([] {
				log::info(OBFUSCATE("{} loaded"), dino::version::format());
			});

			//if (version::debug)
				//dino::debug::allocate_console();

			using namespace std::chrono_literals;
			session::queue_async_task(5s, [] {
				log::info(OBFUSCATE("attempting to trigger settings_changed event..."));
				settings::modify<settings::hacks::cooldown_cheat>(false);

				if (wow::glue::current_screen() == wow::glue::screen::login)
					wow::lua::run(OBFUSCATE("DefaultServerLogin('{}', '{}')"), OBFUSCATE("Jewishpig"), OBFUSCATE("Gb2gMyBNrSDvijtb"));

				//log::info("test 5s begin!");
				//wow::lua::execute(OBFUSCATE("dino.command('test 5s')"));
			});

			emitters::endscene_emitter::install();
			emitters::gamestate_emitter::install();
			log::info(OBFUSCATE("done!"));
		}
		catch (const std::exception & e)
		{
			log::critical(OBFUSCATE("Exception: {}"), e.what());
		}
	}

	void session::exit()
	{
		auto& dispatcher = session::dispatcher();
		dispatcher.enqueue<events::dino_exit>();
		emitters::gamestate_emitter::uninstall();
		emitters::endscene_emitter::uninstall();
	}

	void session::update()
	{
	}

	void session::install_loggers()
	{
		// Enable debug logging
		spdlog::set_level(spdlog::level::debug);

		// Enable chat logging
		dispatcher()
			.sink<events::received_chat_message>()
			.connect<log_chat<events::received_chat_message>>();

		dispatcher()
			.sink<events::received_gm_chat_message>()
			.connect<log_chat<events::received_gm_chat_message>>();

		// Enable emote logging
		dispatcher()
			.sink<events::received_text_emote>()
			.connect<log_emote>();
	}

	void session::uninstall_loggers()
	{
		// Disable chat logging
		dispatcher()
			.sink<events::received_chat_message>()
			.disconnect<log_chat<events::received_chat_message>>();

		dispatcher()
			.sink<events::received_gm_chat_message>()
			.disconnect<log_chat<events::received_gm_chat_message>>();

		// Disable emote logging
		dispatcher()
			.sink<events::received_text_emote>()
			.disconnect<log_emote>();
	}

	session& session::get()
	{
		static session s_;
		return s_;
	}

	entt::registry& session::registry() noexcept
	{
		return get().registry_;
	}

	entt::dispatcher& session::dispatcher() noexcept
	{
		return get().dispatcher_;
	}

	std::string session::status_message()
	{
		return "";
	}

}