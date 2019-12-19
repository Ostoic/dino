#pragma once

#include <boost/mp11/list.hpp>

namespace dino::events::framexml
{
	struct player_entering_world
	{
		bool is_reloading_ui;
	};

	struct player_target_changed
	{
	};

	struct player_leaving_world
	{
		bool is_reloading_ui;
	};

	using player_events = boost::mp11::mp_list<
		player_entering_world,
		player_target_changed,
		player_leaving_world
	>;
}