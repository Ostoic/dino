#pragma once

#include <string_view>
#include <string>

namespace dino::version
{
	// Todo: look at client_services::register_handler
	// to see how we can hook various interesting event handling functions.

	constexpr std::string_view name = "dino";

	constexpr unsigned int major = 0;
	constexpr unsigned int minor = 0;
	constexpr unsigned int build = 1;

#ifndef NDEBUG
	constexpr std::string_view mode = "debug";
#else
	constexpr std::string_view mode = "release";
#endif
	std::string format();
}
