#pragma once

#include "task_handler.hpp"
#include "../events/console_events.hpp"

namespace dino::handlers
{
	class command_handler
	{
	public:
		static command_handler& get() noexcept;

		static bool handle(const events::new_console_command& event);
	};
}