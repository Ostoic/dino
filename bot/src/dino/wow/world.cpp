#include "world.hpp"

#include "glue/glue.hpp"

namespace dino::wow::world
{
	bool ingame()
	{
		return glue::current_screen() == glue::screen::ingame;
	}
}