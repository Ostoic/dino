#include "glue.hpp"

#include <boost/lexical_cast.hpp>

#include "../lua.hpp"

namespace dino::wow::glue
{
	screen current_screen()
	{
		return to_screen(lua::get_text("CURRENT_GLUE_SCREEN"));
	}

	std::string to_string(const screen screen)
	{
		const auto sv = to_string_view(screen);
		return std::string{sv.data(), sv.size()};
	}
}