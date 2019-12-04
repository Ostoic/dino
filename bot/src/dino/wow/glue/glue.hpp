#pragma once

#include <string_view>
#include <string>
#include <array>

namespace dino::wow::glue
{
	using namespace std::literals;
	enum class screen
	{
		login, character_select, character_create,
		realm_wizard, patch_download, trial_convert,
		movie, credits, options, ingame
	};

	constexpr auto screen_names = std::array{
		"login"sv, "charselect"sv, "charcreate"sv,
		"realm_wizard"sv, "patch_download"sv, "trial_convert"sv,
		"movie"sv, "credits"sv, "options"sv, "ingame"sv
	};

	constexpr std::string_view to_string_view(const screen screen)
	{
		return screen_names[static_cast<unsigned int>(screen)];
	}

	constexpr screen to_screen(const std::string_view name)
	{
		for (int s = static_cast<int>(screen::login); s != static_cast<int>(screen::ingame); s++)
		{
			if (screen_names[s] == name)
				return static_cast<screen>(s);
		}

		return screen::ingame;
	}

	std::string to_string(const screen screen);

	screen current_screen();
}
