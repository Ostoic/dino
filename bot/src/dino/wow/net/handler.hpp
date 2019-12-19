#pragma once

#include <cstddef>

#include "messages.hpp"
#include "../data/store.hpp"

namespace dino::wow::net
{
	class handler
	{
	public:
		template <auto Fn>
		static void set_handler(const wow::net::messages::server message)
		{
			const auto set_net_message_handler_
				= bind_fn<void(wow::net::messages::server, void*, wow::data::store*)>
					(wow::offsets::net::client_services::set_message_handler_fn);

			set_net_message_handler_(message, Fn, nullptr);
		}
	};
}