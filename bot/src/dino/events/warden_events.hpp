#pragma once

#include "../wow/data/store.hpp"
#include "../wow/net/messages.hpp"
#include "../wow/offsets.hpp"

#include <boost/mp11/list.hpp>

namespace dino::events
{
	struct received_warden_data
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_warden_data_fn;
		static constexpr auto event_id = wow::net::messages::server::warden_data;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct send_warden_scan
	{
		mutable void** scan_results;
		mutable unsigned int* scan_size;
		mutable bool* drop_packet;
	};

	struct warden_loaded
	{
	};

	struct warden_unloaded
	{
	};

	using warden_events = boost::mp11::mp_list<
		received_warden_data,
		send_warden_scan,
		warden_loaded,
		warden_unloaded
	>;
}