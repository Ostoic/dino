#pragma once

#include "../wow/console.hpp"
#include <boost/mp11/list.hpp>

namespace dino::events
{
	struct new_console_command
	{
		wow::console::command cmd;
	};

	using console_events = boost::mp11::mp_list<
		new_console_command
	>;
}
