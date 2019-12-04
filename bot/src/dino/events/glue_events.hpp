#pragma once

#include "../wow/glue/glue.hpp"

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
}