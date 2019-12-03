#pragma once

#include "../wow/chat.hpp"

namespace dino::events
{
	struct new_chat_message
	{
		mutable wow::chat::message message;
	};
}