#pragma once


namespace dino::events::framexml
{
	struct player_entering_world
	{
		bool is_reloading_ui;
	};

	struct player_leaving_world
	{
		bool is_reloading_ui;
	};
}