#pragma once

#include "../wow/chat/message.hpp"
#include "../wow/chat/emote.hpp"

namespace dino::events
{
	struct received_chat_message
	{
		mutable wow::chat::message message;
		mutable bool* pass;
	};

	struct received_text_emote
	{
		mutable wow::chat::emote emote;
		mutable bool* pass;
	};
}