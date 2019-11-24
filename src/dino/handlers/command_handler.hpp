#pragma once

#include "task_handler.hpp"
#include "../events/console_events.hpp"

namespace dino::handlers
{
	class command_handler
	{
	public:
		static command_handler& get();

		static bool handle(const events::new_console_command& event);

	private:
		//command_handler();

	private:
		friend class session;
	};
}