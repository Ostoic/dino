#pragma once

#include <chrono>
#include <boost/mp11/list.hpp>

namespace dino::events
{
	struct endscene_frame
	{
		std::chrono::milliseconds time_delta;
	};

	using endscene_events = boost::mp11::mp_list<
		endscene_frame
	>;
}