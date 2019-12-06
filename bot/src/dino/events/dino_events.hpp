#pragma once

#include <any>

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
}
