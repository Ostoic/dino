#include "session.hpp"

#include "wow/console.hpp"
#include "wow/chat/message.hpp"
#include "version.hpp"
#include "settings.hpp"

#include "emitters/gamestate_emitter.hpp"
#include "emitters/endscene_emitter.hpp"
#include "emitters/chat_emitter.hpp"
#include "emitters/lua_emitter.hpp"

#include "handlers/command_handler.hpp"
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

// headers for code-to-rewrite

namespace dino
{
	void log_chat(const events::received_chat_message& event)
	{
		const auto text = event.message->text();
		const auto sender = event.message->sender();

		log::info(
			"[{}] [{}]: {}",
			to_string_view(event.message->msg_type()),
			sender,
			text
		);
	}

	void log_emote(const events::received_text_emote& event)
	{
		log::info(
			"{} ->text_emote> {}",
			event.emote->sender_guid(),
			event.emote->target_name()
		);
	}

	void enter_world(const events::gamestate_change_ingame& event)
	{
		log::info("[enter_world] Installing chat_emitter...");
		emitters::chat_emitter::install();
	}

	void session::start()
	{
		try
		{
			wow::console::enable();
			wow::console::open();

			auto& s = session::get();
			s.install_hacks();

			// Setup task handler for .queue_task()
			s.dispatcher_
				.sink<events::endscene_frame>()
				.connect<handlers::task_handler::handle>();

			s.install_loggers();

			// Handle enter_world
			s.dispatcher_
				.sink<events::gamestate_change_ingame>()
				.connect<enter_world>();

			s.dispatcher_
				.sink<events::gamestate_change>()
				.connect<handlers::reinstall_lua_emitter>();

			s.queue_task([] {
				log::info("{} loaded", dino::version::format());
			});

			//if (version::debug)
				//dino::debug::allocate_console();

			emitters::endscene_emitter::install();
			emitters::gamestate_emitter::install();
			log::info("done!");
		}
		catch (const std::exception & e)
		{
			log::critical("Exception: {}", e.what());
		}
	}

	void session::exit()
	{
		auto& dispatcher = get().dispatcher();
		dispatcher.enqueue<events::dino_exit>();
		emitters::gamestate_emitter::uninstall();

		emitters::endscene_emitter::uninstall();
	}

	session& session::get()
	{
		static session s;
		return s;
	}

	void session::update()
	{
	}

	void session::install_hacks()
	{
		if (!settings::hacks::enabled())
			return;

		if (settings::hacks::anti_afk())
		{
			dispatcher_
				.sink<events::endscene_frame>()
				.connect<hacks::anti_afk::tick>();
		}

		if (settings::hacks::translator())
		{
			dispatcher_
				.sink<events::received_chat_message>()
				.connect<hacks::translator::fix_language>();
		}
	}

	void session::install_loggers()
	{
		// Enable chat logging
		dispatcher_
			.sink<events::received_chat_message>()
			.connect<log_chat>();

		// Enable emote logging
		dispatcher_
			.sink<events::received_text_emote>()
			.connect<log_emote>();
	}

	entt::registry& session::registry() noexcept
	{
		return registry_;
	}

	entt::dispatcher& session::dispatcher() noexcept
	{
		return dispatcher_;
	}
}