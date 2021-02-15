#pragma once

#include <any>
#include <string_view>
#include <boost/mp11/list.hpp>

namespace dino::events
{
	struct new_dino_command
	{
		std::string data;
	};

	struct setting_changed
	{
		std::string_view setting_name;
		std::any prev;
	};

	struct dino_exit
	{
	};

	using dino_events = boost::mp11::mp_list<
		new_dino_command,
		setting_changed,
		dino_exit
	>;
}
