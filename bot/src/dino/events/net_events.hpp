#pragma once

#include "../wow/data/store.hpp"
#include "../wow/net/messages.hpp"
#include "../wow/offsets.hpp"

#include <boost/mp11/list.hpp>

namespace dino::events
{
	struct received_wc_connected
	{
		static constexpr auto vmt_slot = 2;
	};

	struct received_wc_disconnected
	{
		static constexpr auto vmt_slot = 4;
	};

	struct received_handle_data
	{
		static constexpr auto vmt_slot = 14;

		mutable void** data;
		mutable unsigned int* size;
	};

	using net_events = boost::mp11::mp_list<
		received_wc_connected,
		received_wc_disconnected,
		received_handle_data
	>;
}