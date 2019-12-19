#pragma once

#include <vector>
#include "../../offset.hpp"

namespace dino::wow::warden
{
	enum class check_type
	{
		memory = 0xF3,
		pageA = 0xB2,
		pageB = 0xBF,
		mpq = 0x98,
		lua_string = 0x8B,
		driver = 0x71,
		timing = 0x57,
		procedure = 0x7E,
		module = 0xD9,
		invalid
	};

	bool is_loaded();

	address singleton();
	address scan_fn();
	address base();

	std::vector<byte> get_key_out();
	std::vector<byte> get_key_in();
}