#pragma once

#include "../wow/net/handler.hpp"
#include "../wow/data/CDataStore.hpp"
#include "../wow/offsets.hpp"

#include "../events/chat_events.hpp"

namespace dino::emitters
{
	template <class Event>
	void make_net_emitter()
	{
		const auto set_net_message_handler_
			= bind_fn<void(wow::net::messages::server, void*, void* param)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		wow::net::set_handler(Event::event_id, wow::net::handle_net_event<Event>);
	}

	template <class Event>
	void restore_net_emitter()
	{
		const auto set_net_message_handler_
			= bind_fn<void(wow::net::messages::server, void*, wow::data::CDataStore*)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		const auto handler = bind_fn<int(int, int, int, void*)>(Event::packet_handler);
		wow::net::set_handler(Event::event_id, handler);
	}
}