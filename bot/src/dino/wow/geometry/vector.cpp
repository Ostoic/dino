#include "vector.hpp"

#include "../offsets.hpp"

namespace dino::wow::geometry
{
	bool vector::is_valid() const
	{
		return is_valid_position(*this);
	}


	bool is_valid_position(const vector& vector)
	{
		const auto is_valid_position_ = bind_fn<bool(const geometry::vector*, float)>(offsets::world::is_valid_position_fn);

		return is_valid_position_(&vector, 2.f);
	}
}