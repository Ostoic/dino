#pragma once

#include <string>

namespace dino::wow::glue
{
	enum class screen
	{
		login, character_select, character_create,
		realm_wizard, patch_download, trial_convert,
		movie, credits, options
	};

	screen current_screen();
}
