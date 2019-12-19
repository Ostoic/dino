#pragma once

#include <string>
#include <filesystem>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "../session.hpp"

namespace dino::wow::spell
{
	enum class cast_flags : std::uint32_t
	{
		slot00 = 0x00000000,
		slot01 = 0x00000001,
		slot02 = 0x00000002,
		slot03 = 0x00000004,
		slot04 = 0x00000008,
		slot05 = 0x00000010,
		slot06 = 0x00000020,
		slot07 = 0x00000040,
		slot08 = 0x00000080,
		slot09 = 0x00000100,
		slot10 = 0x00000200,
		slot11 = 0x00000400,
		slot12 = 0x00000800,
		slot13 = 0x00001000,
		slot14 = 0x00002000,
		slot15 = 0x00004000,
		slot16 = 0x00008000,
		slot17 = 0x00010000,
		slot18 = 0x00020000,
		slot19 = 0x00040000,
		slot20 = 0x00080000,
		slot21 = 0x00100000,
		slot22 = 0x00200000,
		slot23 = 0x00400000,
		slot24 = 0x00800000,
		slot25 = 0x01000000,
		slot26 = 0x02000000,
		slot27 = 0x04000000,
		slot28 = 0x08000000,
		slot29 = 0x10000000,
		slot30 = 0x20000000,
		slot31 = 0x40000000,
		slot32 = 0x80000000
	};
}
