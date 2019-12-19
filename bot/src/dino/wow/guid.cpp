#include "guid.hpp"
#include "offsets.hpp"

#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <iostream>

namespace dino::wow
{
	guid::guid(std::string value)
		: guid{deref_as<std::uint64_t(const char*)>(wow::offsets::guid::string_to_guid)(value.c_str())}
	{}

}
