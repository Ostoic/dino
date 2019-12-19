#include "traceline.hpp"

namespace dino::wow::world
{
	hit_result traceline(const geometry::vector& start, const geometry::vector& end, float max_distance, hit_test flags)
	{
		const auto original_traceline = bind_fn<
			bool(
				const geometry::vector*,
				const geometry::vector*,
				geometry::vector*,
				float,
				hit_test,
				int
			)>(offsets::world::traceline_fn);

		auto out = geometry::vector{};
		const auto result = original_traceline(
			&start,
			&end,
			&out,
			max_distance,
			flags,
			0
		);

		return hit_result{out, result};
	}

	unsigned int trace_count()
	{
		return deref_as<unsigned int>(offsets::world::trace_count);
	}
}