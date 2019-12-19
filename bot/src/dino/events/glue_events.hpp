#pragma once

#include "../wow/glue/glue.hpp"
#include <boost/mp11/list.hpp>

namespace dino::events
{
	struct gamestate_change
	{
		wow::glue::screen before;
		wow::glue::screen after;
	};

	struct gamestate_change_login : gamestate_change
	{
	};

	struct gamestate_change_ingame : gamestate_change
	{
	};

	using glue_events = boost::mp11::mp_list<
		gamestate_change,
		gamestate_change_login,
		gamestate_change_ingame
	>;
}