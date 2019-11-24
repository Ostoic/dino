#include "settings.hpp"

namespace dino::settings
{
	float fps = 60;

	std::chrono::milliseconds refresh_rate() noexcept
	{
		return std::chrono::milliseconds{static_cast<unsigned int>(1000.f / settings::fps)};
	}
}