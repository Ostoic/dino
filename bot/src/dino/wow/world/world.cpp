#define NOMINMAX
#include "world.hpp"
		
#include <algorithm>

#include "../../internal/string.hpp"
#include "../../log.hpp"
#include "../net/messages.hpp"

namespace dino::wow::world
{
	__declspec(naked) void client_services::prehook_send_packet(wow::data::CDataStore* data)
	{
		_asm
		{
			pushad;
			pushfd;
		}
		
		static auto original_send_packet_fn = static_cast<address::address_type>(wow::offsets::net::client_services::send_packet_fn);

		[] (auto* data) {
			std::vector<byte> bytes;
			log::debug(OBFUSCATE("[client_services::hooked_send_packet] hello"));
			log::debug(OBFUSCATE("[client_services::hooked_send_packet] packet size: {}"), data->m_size);

			std::copy(data->m_buffer, data->m_buffer + data->m_size, std::back_inserter(bytes));
			log::debug(OBFUSCATE("[client_services::hooked_send_packet] bytes: {}"), internal::format_bytes(bytes.begin(), bytes.end()));
			log::debug(OBFUSCATE("[client_services::hooked_send_packet] bytes size: {}"), bytes.size());
		}(data);

		_asm
		{
			popfd;
			popad;
			jmp original_send_packet_fn;
		};
	}

	//namespace time = std::chrono;
	//time::clock::time_point get_async_time();
}