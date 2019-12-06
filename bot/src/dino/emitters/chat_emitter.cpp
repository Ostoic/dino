#include "chat_emitter.hpp"

#include "../wow/net/messages.hpp"
#include "../wow/data/store.hpp"
#include "../wow/data/message_store.hpp"
#include "../session.hpp"

#include "../events/chat_events.hpp"
#include "../wow/offsets.hpp"
#include "../log.hpp"

#include "set_message_handler.hpp"

#include <obfuscator.hpp>

namespace dino::emitters
{
	namespace
	{
		void smsg_chat_emitter(int a1, int a2, int a3, void* cdata)
		{
			auto original_handler
				= bind_fn<int(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_messagechat_fn);

			bool pass = false;
			auto event = events::received_chat_message{wow::data::message_store{wow::data::store{cdata}}, &pass};
			auto& dispatcher = dino::session::get().dispatcher();

			// Queue a received_chat_message event for the dispatcher
			dispatcher.enqueue<events::received_chat_message>(event);

			// Trigger the event
			dispatcher.update<events::received_chat_message>();

			if (pass)
				return;

			original_handler(a1, a2, a3, cdata);
		}

		void smsg_gm_chat_emitter(int a1, int a2, int a3, void* cdata)
		{
			auto original_handler
				= bind_fn<int(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_gm_messagechat_fn);

			bool pass = false;
			auto event = events::received_chat_message{wow::data::message_store{wow::data::store{cdata}, true}, &pass};
			auto& dispatcher = dino::session::get().dispatcher();

			// Queue a received_chat_message event for the dispatcher
			dispatcher.enqueue<events::received_chat_message>(event);

			// Trigger the event
			dispatcher.update<events::received_chat_message>();

			if (pass)
				return;

			original_handler(a1, a2, a3, cdata);
		}

		void smsg_text_emote_emitter(int a1, int a2, int a3, void* cdata)
		{
			auto original_handler
				= bind_fn<int(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_text_emote_fn);

			bool pass = false;
			auto event = events::received_text_emote{wow::chat::emote{wow::data::store{cdata}}, &pass};
			auto& dispatcher = dino::session::get().dispatcher();

			// Queue a received_chat_message event for the dispatcher
			dispatcher.enqueue(event);

			// Trigger the event
			dispatcher.update<decltype(event)>();

			if (pass)
				return;

			original_handler(a1, a2, a3, cdata);
		}
	}

	void chat_emitter::install()
	{
		emitters::set_net_message_handler(
			wow::net::messages::server::text_emote,
			smsg_text_emote_emitter
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::chat_message,
			smsg_chat_emitter
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::gm_chat_message,
			smsg_gm_chat_emitter
		);

		log::info(OBFUSCATE("[chat_emitter] installed"));
	}

	void chat_emitter::uninstall()
	{
		emitters::set_net_message_handler(
			wow::net::messages::server::text_emote,
			bind_fn<void(wow::net::messages::server, void*, wow::data::store*)>
				(wow::offsets::net::messages::packet_smsg_text_emote_fn)
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::chat_message,
			bind_fn<void(wow::net::messages::server, void*, wow::data::store*)>
				(wow::offsets::net::messages::packet_smsg_messagechat_fn)
		);

		emitters::set_net_message_handler(
			wow::net::messages::server::gm_chat_message,
			bind_fn<void(wow::net::messages::server, void*, wow::data::store*)>
				(wow::offsets::net::messages::packet_smsg_gm_messagechat_fn)
		);

		log::info(OBFUSCATE("[chat_emitter] uninstalled"));
	}
}