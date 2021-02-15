#define NOMINMAX
#include "world.hpp"

#include <algorithm>

#include "../../internal/string.hpp"
#include "../../log.hpp"

namespace dino::wow::world
{
	void client_services::hooked_send_packet(wow::data::CDataStore* data)
	{
		log::debug(OBFUSCATE("[client_services::hooked_send_packet] hello"));
		log::debug(OBFUSCATE("[client_services::hooked_send_packet] data[0:min(len, 10)]: "), internal::format_bytes(data->m_buffer, data->m_buffer + 2));
		this->call_original_send_packet_(data);
	}

	void client_services::call_original_send_packet_(wow::data::CDataStore* data)
	{
		const auto send_packet_fn = deref_as<fn_ptr<void(client_services*, wow::data::CDataStore*)>>(wow::offsets::net::client_services::send_packet_fn);
		send_packet_fn(this, data);
		log::debug(OBFUSCATE("[client_services::call_original_send_packet_] original called!"));
	}

	//namespace time = std::chrono;
	//time::clock::time_point get_async_time();
}