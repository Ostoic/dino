#pragma once

#include "../events/console_events.hpp"
#include "../events/chat_events.hpp"
#include "../events/dino_events.hpp"

namespace dino::handlers
{
	class command_handler
	{
	public:
		static command_handler& get() noexcept;

		static bool handle_console(const events::new_console_command& event);
		static void handle_chat(const events::received_chat_message& event);
		static void handle(const events::new_dino_command& event);
	};
}