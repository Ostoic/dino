#pragma once

#include <any>
#include <boost/mp11/list.hpp>

namespace dino::events
{
	struct new_dino_command
	{
		std::string data;
	};

	template <auto Setting>
	struct setting_changed
	{
		std::any prev;
	};

	struct dino_exit
	{
	};

	template <auto Setting>
	using dino_events = boost::mp11::mp_list<
		new_dino_command,
		setting_changed<Setting>,
		dino_exit
	>;
}
