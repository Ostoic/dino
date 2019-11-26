#include "graphics.hpp"

namespace dino::wow::graphics
{
	dino::address get_ptr_address()
	{
		return
			bind_value(
				bind_value(
					bind_value(offsets::dx::device_ptr_base)
					+ offsets::dx::device_ptr_off
				)
			) + offsets::dx::endscene_off;
	}
}