#pragma once

#include "../wow/data/message_store.hpp"
#include "../wow/chat/emote.hpp"

namespace dino::events
{
	struct received_chat_message
	{
		mutable wow::data::message_store message;
		mutable bool* pass;
	};

	struct received_text_emote
	{
		mutable wow::chat::emote emote;
		mutable bool* pass;
	};
}