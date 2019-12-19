#pragma once

#include <cstdint>

#include "../geometry/vector.hpp"

namespace dino::wow::movement
{
	class spline
	{
	public:
		enum class type{normal, stop, facing_spot, facing_target, facing_angle};
		enum class mode{linear, camull_rom, bezier3};
		enum class flags : std::uint32_t
		{
			none = 0x0,
			forward = 0x1,
			backward = 0x2,
			strafe_left = 0x4,
			strafe_right = 0x8,
			turn_left = 0x10,
			turn_right = 0x20,
			pitch_up = 0x40,
			pitch_down = 0x80,
			done = 0x100,
			falling = 0x200,
			no_spline = 0x400,
			trajectory = 0x800,
			walk_mode = 0x1000,
			flying = 0x2000,
			knockback = 0x4000,
			final_point = 0x8000,
			final_target = 0x10000,
			final_orient = 0x20000,
			catmull_rom = 0x40000,

			unknown1 = 0x80000,
			unknown2 = 0x100000,
			unknown3 = 0x200000,
			unknown4 = 0x400000,
			unknown5 = 0x800000,
			unknown6 = 0x1000000,
			unknown7 = 0x2000000,
			unknown8 = 0x4000000,
			unknown9 = 0x8000000,
			unknown10 = 0x10000000,
			unknown11 = 0x20000000,
			unknown12 = 0x40000000,
			unknown13 = 0x80000000,
		};

	public:


	private:
		flags flags_;
		geometry::vector pos_;
		std::uint32_t id_;
		float rotation_;
	};


}