#include "command_handler.hpp"
#include "../version.hpp"

#include <unordered_set>

namespace dino::handlers
{
	command_handler& command_handler::get()
	{
		static command_handler singleton;
		return singleton;
	}

	bool command_handler::handle(const events::new_console_command& event)
	{
		const auto& cmd = event.cmd;
		static std::unordered_set<std::uint32_t> serviced_lines;
		if (serviced_lines.contains(cmd.line_number()))
			return true;

		serviced_lines.emplace(cmd.line_number());
		if (cmd.cmd() == "dino::version")
		{
			wow::console::dino("Welcome to {}", dino::version::name);
			return true;
		}

		return false;
	}
}