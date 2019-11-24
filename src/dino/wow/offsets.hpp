#pragma once

#include "../offset.hpp"

namespace dino::wow::offsets
{
	namespace console
	{
		constexpr auto enabled = address{0x00CABCC4};
		constexpr auto active = address{0x00CA1978};
		constexpr auto num_lines = address{0x00CA197C};

		constexpr auto keybind = address{0x00ADBAC4};

		constexpr auto write_fn = address{0x00765270};
		constexpr auto register_fn = address{0x00769100};
		constexpr auto clear_fn = address{0x007644B0};

		constexpr auto last_line = address{0x00CABA58};
	}

	namespace object_manager
	{
	}

	namespace time
	{

	}

	namespace dx
	{
		constexpr auto device_ptr_base = address{0x00C5DF88};
		constexpr auto device_ptr_off = address{0x397C};

		constexpr auto beginscene_off = address{0xA4};
		constexpr auto endscene_off = address{0xA8};
	}
}
