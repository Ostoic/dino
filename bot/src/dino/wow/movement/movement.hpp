#pragma once

#include <cstdint>

namespace dino::wow::movement
{
	enum class flags : std::uint32_t
	{
		none = 0x0,
		forward = 0x1,
		backward = 0x2,

		strafe_left = 0x4,
		strafe_right = 0x8,

		turn_left = 0x10,
		turn_right = 0x20,

		pictch_up = 0x40,
		pitch_down = 0x80,

		walk_mode = 0x100,
		on_transport = 0x200,
		levitating = 0x400,
		root = 0x800,

		falling = 0x1000,
		falling_far = 0x2000,

		pending_stop = 0x4000,
		pending_strafe_stop = 0x8000,
		pending_forward = 0x10000,
		pending_backward = 0x20000,
		pending_strafe_left = 0x40000,
		pending_strafe_right = 0x80000,
		pending_root = 0x100000,

		swimming = 0x200000,
		ascending = 0x400000,
		descending = 0x800000,

		can_fly = 0x1000000,
		flying = 0x2000000,

		spline_elevation = 0x4000000,
		spline_enabled = 0x8000000,

		water_walking = 0x10000000,
		safe_fall = 0x20000000,
		hover = 0x40000000,
	};

	enum class flags2 : std::uint8_t
	{
		none = 0x0,
		unknown1 = 0x1,
		unknown2 = 0x2,
		unknown3 = 0x4,

		full_speed_turning = 0x8,
		full_speed_pitching = 0x10,
		always_allow_pitching = 0x20,

		unknown4 = 0x40,
		unknown5 = 0x80,
		unknown6 = 0x100,
		unknown7 = 0x200,

		interpolated_player_movement = 0x400,
		interpolated_player_turning = 0x800,
		interpolated_player_pitching = 0x1000,

		unknown8 = 0x2000,
		unknown9 = 0x4000,
		unknown10 = 0x8000,
	};
}