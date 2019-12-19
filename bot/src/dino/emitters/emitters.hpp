#pragma once

#include "../wow/net/handler.hpp"
#include "../wow/data/CDataStore.hpp"
#include "../wow/data/store.hpp"
#include "../wow/offsets.hpp"
#include "../session.hpp"
#include "../offset.hpp"

#include "../events/chat_events.hpp"

#include <typeinfo>

namespace dino::emitters
{
	template <class Fn>
	void make_net_emitter(const wow::net::messages::server message, Fn&& fn)
	{
		const auto set_net_message_handler_
			= bind_fn<void(wow::net::messages::server, void*, void*)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		set_net_message_handler_(message, std::forward<Fn>(fn), nullptr);
	}

	template <class Event>
	int handle_net_event(int a1, int a2, int a3, wow::data::CDataStore* cdata)
	{
		using store_t = decltype(Event::store);

		bool drop_packet = false;

		try
		{
			// Queue Event event
			dispatcher::enqueue(Event{store_t{cdata}, &drop_packet});

			// Signal Event handlers
			dispatcher::update<Event>();
		}
		catch (const std::exception& e)
		{
			log::error("[handle_net_event] Exception occured: {}", e.what());
		}

		if (drop_packet)
			return -1;

		const auto original_handler = bind_fn<int(int, int, int, wow::data::CDataStore*)>(Event::packet_handler);
		return original_handler(a1, a2, a3, cdata);
	}

	template <class Event>
	void make_net_emitter()
	{
		const auto set_net_message_handler_
			= bind_fn<void(wow::net::messages::server, void*, void* param)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		set_net_message_handler_(Event::event_id, emitters::handle_net_event<Event>, nullptr);
	}

	template <class Event>
	void restore_net_emitter()
	{
		const auto set_net_message_handler_
			= bind_fn<void(wow::net::messages::server, void*, wow::data::CDataStore*)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		const auto handler = bind_fn<int(int, int, int, void*)>(Event::packet_handler);
		set_net_message_handler_(Event::event_id, handler, nullptr);
	}
}