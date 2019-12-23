#pragma once

#include <chrono>

namespace dino::settings
{
	namespace hacks
	{
		bool is_enabled() noexcept;
		bool anti_afk() noexcept;
		bool translator() noexcept;
	};

	std::chrono::milliseconds refresh_rate() noexcept;
	float fps() noexcept;
}