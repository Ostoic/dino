#pragma once

#include "../wow/net/messages.hpp"
#include "../wow/data/store.hpp"
#include "../wow/offsets.hpp"

namespace dino::emitters
{
	template <class Fn>
	void set_net_message_handler(const wow::net::messages::server message, Fn&& fn)
	{
		auto set_net_message_handler_
			= bind_fn<void(wow::net::messages::server, void*, wow::data::store*)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		set_net_message_handler_(message, std::forward<Fn>(fn), nullptr);
	}
}