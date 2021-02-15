#pragma once

#include <chrono>

#include "../offsets.hpp"
#include "../data/CDataStore.hpp"

namespace dino::wow::world
{
	class client_services
	{
	public:
		void hooked_send_packet(wow::data::CDataStore* data);

	private:
		void call_original_send_packet_(wow::data::CDataStore* data);
		
	};
	//namespace time = std::chrono;
	//time::clock::time_point get_async_time();
}