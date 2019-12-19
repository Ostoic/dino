#pragma once

#include "../wow/data/store.hpp"
#include "../wow/net/messages.hpp"
#include "../wow/offsets.hpp"

#include <boost/mp11/list.hpp>

namespace dino::events
{
	struct received_server_message
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_server_message_fn;
		static constexpr auto event_id = wow::net::messages::server::server_message;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	using server_events = boost::mp11::mp_list<
		received_server_message
	>;
}