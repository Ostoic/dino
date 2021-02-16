#pragma once

#include <chrono>

#include "../offsets.hpp"
#include "../data/CDataStore.hpp"

namespace dino::wow::world
{
	class client_services
	{
	public:
		void prehook_send_packet(wow::data::CDataStore* data);

	};
	//namespace time = std::chrono;
	//time::clock::time_point get_async_time();
}