#pragma once

#include "../wow/net/messages.hpp"
#include "../wow/data/store.hpp"
#include "../wow/offsets.hpp"
#include "../session.hpp"
#include "../offset.hpp"

#include <typeinfo>

namespace dino::emitters
{
	template <class Fn>
	void make_net_emitter(const wow::net::messages::server message, Fn&& fn)
	{
		const auto set_net_message_handler_
			= bind_fn<void(wow::net::messages::server, void*, wow::data::store*)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		set_net_message_handler_(message, std::forward<Fn>(fn), nullptr);
	}

	template <class Event>
	void handle_net_event(int a1, int a2, int a3, void* cdata)
	{
		using store_t = decltype(Event::store);

		auto& dispatcher = dino::session::dispatcher();
		bool drop_packet = false;

		// Queue Event event
		dispatcher.enqueue(Event{store_t{address{cdata}}, &drop_packet});

		// Signal Event handlers
		dispatcher.update<Event>();

		if (drop_packet)
			return;

		const auto original_handler = bind_fn<void(int, int, int, void*)>(Event::packet_handler);
		original_handler(a1, a2, a3, cdata);
	}

	template <class Event>
	void make_net_emitter()
	{
		const auto set_net_message_handler_
			= bind_fn<void(wow::net::messages::server, void*, wow::data::store*)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		set_net_message_handler_(Event::event_id, emitters::handle_net_event<Event>, nullptr);
	}

	template <class Event>
	void restore_net_emitter()
	{
		const auto set_net_message_handler_
			= bind_fn<void(wow::net::messages::server, void*, wow::data::store*)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		const auto handler = bind_fn<void(int, int, int, void*)>(Event::packet_handler);
		set_net_message_handler_(Event::event_id, handler, nullptr);
	}
}