#include "connection.hpp"
#include "../offsets.hpp"

namespace dino::wow::net
{
	std::size_t num_sent_packets()
	{
		return deref_as<unsigned int>(offsets::net::num_sent_packets);
	}

	std::size_t num_received_packets()
	{
		return deref_as<unsigned int>(offsets::net::num_received_packets);
	}

	std::size_t num_sent_bytes()
	{
		return deref_as<unsigned int>(offsets::net::num_sent_bytes);
	}

	std::size_t num_received_bytes()
	{
		return deref_as<unsigned int>(offsets::net::num_received_bytes);
	}
}