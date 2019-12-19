#pragma once

#include <string>
#include <boost/mp11/list.hpp>

namespace dino::events::framexml
{
	struct received_ui_error_message
	{
		mutable std::string data;
	};

	struct received_ui_info_message
	{
		mutable std::string data;
	};

	using ui_events = boost::mp11::mp_list<
		received_ui_error_message,
		received_ui_info_message
	>;
}