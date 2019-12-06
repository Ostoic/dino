#pragma once

#include "../wow/data/message_store.hpp"
#include "../wow/chat/emote.hpp"

#include "../wow/net/messages.hpp"
#include "../wow/offsets.hpp"

namespace dino::events
{
	struct received_chat_message
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_messagechat_fn;
		static constexpr auto event_id = wow::net::messages::server::chat_message;

		mutable wow::data::message_store<false> store;
		mutable bool* drop_packet;
	};

	struct received_gm_chat_message
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_gm_messagechat_fn;
		static constexpr auto event_id = wow::net::messages::server::gm_chat_message;

		mutable wow::data::message_store<true> store;
		mutable bool* drop_packet;
	};

	struct received_text_emote
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_text_emote_fn;
		static constexpr auto event_id = wow::net::messages::server::text_emote;

		mutable wow::chat::emote store;
		mutable bool* drop_packet;
	};
}