#pragma once

#include <chrono>
#include <string_view>

namespace dino::wow::world
{
	namespace time = std::chrono;
	using clock = time::high_resolution_clock;
	using namespace std::literals::string_view_literals;

	enum class timing_method{best, get_tick_count, query_perf};

	constexpr auto timing_method_names = std::array{
		"best"sv, "get_tick_count"sv, "query_perf"sv, "unknown"sv
	};

	constexpr std::string_view to_string(const timing_method method)
	{
		const auto index = static_cast<unsigned int>(method);
		if (method < timing_method::best || method > timing_method::query_perf)
			return "unknown"sv;

		return timing_method_names[static_cast<unsigned int>(method)];
	}

	clock::time_point last_action_time();
	clock::time_point timestamp();

	void set_last_action_time(clock::time_point point);
	void set_timestamp(clock::time_point point);

	timing_method get_timing_method();

	clock::time_point get_async_time();
}