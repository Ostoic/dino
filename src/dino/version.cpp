#include "version.hpp"

#include <fmt/format.h>
#include <string_view>
#include <random>
#include <ctime>

namespace dino::version
{
	std::string format()
	{
		using namespace std::literals;
		constexpr auto dank_names = std::array{
			"dino"sv,
			"dinoman"sv,
			"young-dinner-boy"sv,
			"dinolegs"sv,
		};

		std::random_device seed;
		auto gen = std::default_random_engine{seed()};
		auto uniform = std::uniform_int_distribution<int>{0, dank_names.size() - 1};

		return fmt::format(
			"{} [{}] {}.{}.{}",
			dank_names[uniform(gen)], version::mode,
			version::major, version::minor, version::build
		);
	}
}