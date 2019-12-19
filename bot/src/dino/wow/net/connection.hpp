#pragma once

#include <cstddef>

namespace dino::wow::net
{
	class connection
	{
	public:

	private:
	};


	std::size_t num_sent_packets();
	std::size_t num_received_packets();

	std::size_t num_sent_bytes();
	std::size_t num_received_bytes();
}