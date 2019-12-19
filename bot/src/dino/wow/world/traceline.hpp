#pragma once

#include "../offsets.hpp"
#include "../geometry/vector.hpp"

namespace dino::wow::world
{
	enum class hit_test
	{
		nothing = 0x0,

		// Boundary of models
		bounding_models = 0x1,

		// World Model Objects, such as the goldshire inn, stormwind auction house, etc
		wmo = 0x10,

		// Used in ClickTerrain
		unknown = 0x40,

		// The terrain
		ground = 0x100,

		// Tested on water - should work on lava and such too
		liquid = 0x10000,

		// This works for liquid, but also for some other unknown purpose.
		unknown2 = 0x20000,

		// UC elevator doors, etc
		movable_objects = 0x100000,

		line_of_sight = wmo | bounding_models | movable_objects,
		ground_and_structures = line_of_sight | ground,

	};

	struct hit_result
	{
		geometry::vector out;
		bool result;
	};

	hit_result traceline(const geometry::vector& start, const geometry::vector& end, float max_distance, hit_test flags);

	template <hit_test Flags>
	hit_result traceline(const geometry::vector& start, const geometry::vector& end, float max_distance)
	{
		return traceline(start, end, max_distance, Flags);
	}

	unsigned int trace_count();
}