#include "time.hpp"
#include "../offsets.hpp"
#include "../../log.hpp"

namespace dino::wow::world
{
	clock::time_point last_action_time()
	{
		const auto last_action = deref_as<unsigned int>(wow::offsets::world::time::last_action);
		auto ms = time::milliseconds{last_action};

		return clock::time_point{time::duration_cast<time::nanoseconds>(ms)};
	}

	clock::time_point timestamp()
	{
		const auto timestamp = deref_as<unsigned int>(wow::offsets::world::time::timestamp);
		const auto ms = time::milliseconds{timestamp};

		return clock::time_point{time::duration_cast<time::nanoseconds>(ms)};
	}

	void set_last_action_time(const clock::time_point point)
	{
		auto& last_action = deref_as<unsigned int>(wow::offsets::world::time::last_action);

		const auto ms = time::duration_cast<time::milliseconds>(point.time_since_epoch());
		last_action = static_cast<unsigned int>(ms.count());
	}

	void set_timestamp(const clock::time_point point)
	{
		auto& timestamp = deref_as<unsigned int>(wow::offsets::world::time::timestamp);

		const auto ms = time::duration_cast<time::milliseconds>(point.time_since_epoch());
		timestamp = static_cast<unsigned int>(ms.count());
	}

	timing_method get_timing_method()
	{
		const auto base = deref_as<address>(offsets::world::time::singleton);
		return deref_as<timing_method>(base + offsets::world::time::timing_method_offset);
	}

	clock::time_point get_async_time()
	{
		const auto& get_time = deref_as<std::uint64_t()>(offsets::world::get_async_time_ms_fn);
		const auto tick_count = get_time();

		const auto now = clock::now();

		log::info(
			OBFUSCATE("[get_async_time] timing_method: {}"),
			to_string(wow::world::get_timing_method())
		);

		if (wow::world::get_timing_method() == wow::world::timing_method::query_perf)
		{
			auto ms = time::milliseconds{tick_count};
			log::info(
				OBFUSCATE("[get_async_time] tick_count: {}, now.count(): {}"),
				ms.count(),
				time::duration_cast<time::milliseconds>(now.time_since_epoch()).count()
			);

			const auto time_point = clock::time_point{time::duration_cast<time::nanoseconds>(ms)};
			return time_point;
		}

		return now;
	}
}