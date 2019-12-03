#pragma once

#include <chrono>

namespace dino::events
{
	struct endscene_frame
	{
		std::chrono::milliseconds time_delta;
	};
}