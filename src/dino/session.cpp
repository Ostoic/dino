#include "session.hpp"

#include "wow/console.hpp"
#include "wow/graphics.hpp"
#include "version.hpp"

#include "handlers/task_handler.hpp"
#include "handlers/command_handler.hpp"
#include "events/console_events.hpp"

#include <unordered_set>

namespace dino
{
	session& session::start()
	{
		static session singleton;
		return singleton;
	}

	session& session::get()
	{
		return session::start();
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
		dispatcher_.update();
	}

	session::session()
	{
		using namespace std::chrono_literals;

		wow::console::enable();
		wow::console::open();
		handlers::task_handler::install_hook();

		dispatcher_
			.sink<events::new_console_command>()
			.connect<handlers::command_handler::handle>();

		this->queue_task([]{
			wow::console::dino("{} loaded", dino::version::format());
		});
	}

	session::~session()
	{
		handlers::task_handler::uninstall_hook();
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