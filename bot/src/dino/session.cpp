#include "session.hpp"

#include "wow/console.hpp"
#include "wow/graphics.hpp"
#include "wow/chat.hpp"
#include "version.hpp"
#include "settings.hpp"

#include "emitters/endscene_emitter.hpp"
#include "emitters/chat_emitter.hpp"

#include "handlers/command_handler.hpp"
#include "events/console_events.hpp"
#include "events/endscene_events.hpp"
#include "hacks/translator.hpp"
#include "hacks/anti_afk.hpp"

#include <unordered_set>
#include <spdlog/spdlog.h>

// headers for code-to-rewrite
#include "debug.hpp"

namespace dino
{
	void print_chat(const events::new_chat_message& event)
	{
		wow::console::dino(
			"[{}] [{}]: {}",
			static_cast<int>(event.message->msg_type()),
			event.message->sender(),
			event.message->text()
		);

		spdlog::info(
			"[{}] [{}]: {}",
			static_cast<int>(event.message->msg_type()),
			event.message->sender(),
			event.message->text()
		);
	}

	void session::start()
	{
		try
		{
			const auto file_logger = spdlog::basic_logger_mt("dino.log", "logs/dino.log");
			spdlog::set_default_logger(file_logger);

			wow::console::enable();
			wow::console::open();

			auto& s = session::get();
			s.dispatcher_
				.sink<events::new_console_command>()
				.connect<handlers::command_handler::handle>();

			if (settings::hacks::anti_afk())
			{
				s.dispatcher_
					.sink<events::endscene_frame>()
					.connect<hacks::anti_afk::tick>();
			}

			if (settings::hacks::translator())
			{
				s.dispatcher_
					.sink<events::new_chat_message>()
					.connect<hacks::translator::fix_language>();
			}

			s.dispatcher_
				.sink<events::endscene_frame>()
				.connect<handlers::task_handler::handle>();

			s.dispatcher_
				.sink<events::new_chat_message>()
				.connect<print_chat>();

			s.queue_task([] {
				wow::console::dino("{} loaded", dino::version::format());
			});

			if (version::debug)
				dino::debug::allocate_console();

			wow::console::dino("installing emitters...");
			emitters::endscene_emitter::install();
			emitters::chat_emitter::install();

			wow::console::dino("installing handlers...");
			wow::console::dino("done!");
		}
		catch (const std::exception & e)
		{
			wow::console::dino("Exception: {}", e.what());
		}
	}

	void session::exit()
	{
		wow::console::close();
		wow::console::disable();
		emitters::chat_emitter::uninstall();
		emitters::endscene_emitter::uninstall();
	}

	session& session::get()
	{
		static session s;
		return s;
	}

	void session::update_console_commands()
	{
		static unsigned int last_line_executed = 0;
		if (wow::console::num_lines() != last_line_executed)
		{
			dispatcher_.enqueue(events::new_console_command{wow::console::last_command()});
			last_line_executed = wow::console::num_lines();
		}
	}

	void session::update()
	{
		this->update_console_commands();
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