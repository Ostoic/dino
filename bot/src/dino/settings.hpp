#pragma once

#include <chrono>

namespace dino::settings
{
	extern float fps;

	std::chrono::milliseconds refresh_rate() noexcept;
}
