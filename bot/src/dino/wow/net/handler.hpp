#pragma once

#include <concepts>

#include "messages.hpp"
#include "../data/store.hpp"
#include "../../scheduler.hpp"

namespace dino::wow::net
{
	// handler concept
	template <class Fn>
	void set_handler(const wow::net::messages::server message, Fn&& fn)
	{
		if constexpr (!std::is_invocable<Fn, int, int, int data::CDataStore*>)
			static_assert(false, "[wow] [net] [set_handler] Function must be invocable in the form: int(int, int, int, data::CDataStore*)")

		const auto set_net_message_handler_
			= bind_fn<void(wow::net::messages::server, void*, void*)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		set_net_message_handler_(message, std::forward<Fn>(fn), nullptr);
	}

	template <class Event>
	int handle_net_event(int a1, int a2, int a3, data::CDataStore* cdata)
	{
		using store_t = decltype(Event::store);

		bool drop_packet = false;

		try
		{
			// Queue Event event
			scheduler::enqueue(Event{store_t{cdata}, &drop_packet});

			// Signal Event handlers
			scheduler::update<Event>();
		}
		catch (const std::exception& e)
		{
			log::error("[handle_net_event] Exception occured: {}", e.what());
		}

		if (drop_packet)
			return -1;

		const auto original_handler = bind_fn<int(int, int, int, data::CDataStore*)>(Event::packet_handler);
		return original_handler(a1, a2, a3, cdata);
	}
}