#include "chat_emitter.hpp"

#include "../wow/net/messages.hpp"
#include "../wow/data_store.hpp"
#include "../wow/chat.hpp"
#include "../session.hpp"

#include "../events/chat_events.hpp"
#include "../wow/offsets.hpp"

namespace dino::emitters
{
	chat_emitter& chat_emitter::get() noexcept
	{
		static chat_emitter me;
		return me;
	}

	static int smsg_chat_emitter(int a1, int a2, int a3, void* cdata)
	{
		auto original_handler
			= bind_fn<int(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_messagechat_fn);

		auto event = events::new_chat_message{wow::chat::message{wow::data_store{cdata}}};
		auto& dispatcher = dino::session::get().dispatcher();

		// Queue a new_chat_message event for the dispatcher
		dispatcher.enqueue<events::new_chat_message>(event);

		// Trigger the event
		dispatcher.update<events::new_chat_message>();

		return original_handler(a1, a2, a3, cdata);
	}

	static int smsg_gm_chat_emitter(int a1, int a2, int a3, void* cdata)
	{
		auto original_handler
			= bind_fn<int(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_gm_messagechat_fn);

		auto event = events::new_chat_message{wow::chat::message{wow::data_store{cdata}}};
		auto& dispatcher = dino::session::get().dispatcher();

		// Queue a new_chat_message event for the dispatcher
		dispatcher.enqueue<events::new_chat_message>(event);

		// Trigger the event
		dispatcher.update<events::new_chat_message>();

		return original_handler(a1, a2, a3, cdata);
	}

	void chat_emitter::install()
	{
		auto set_message_handler
			= bind_fn<void(wow::net::messages::server, void*, wow::data_store*)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		set_message_handler(
			wow::net::messages::server::chat_message,
			smsg_chat_emitter,
			nullptr
		);

		set_message_handler(
			wow::net::messages::server::gm_chat_message,
			smsg_gm_chat_emitter,
			nullptr
		);
	}

	void chat_emitter::uninstall()
	{
		auto set_message_handler
			= bind_fn<void(wow::net::messages::server, void*, wow::data_store*)>
				(wow::offsets::net::client_services::set_message_handler_fn);

		set_message_handler(
			wow::net::messages::server::chat_message,
			bind_fn<void(wow::net::messages::server, void*, wow::data_store*)>
				(wow::offsets::net::messages::packet_smsg_messagechat_fn),
			nullptr
		);

		set_message_handler(
			wow::net::messages::server::gm_chat_message,
			bind_fn<void(wow::net::messages::server, void*, wow::data_store*)>
				(wow::offsets::net::messages::packet_smsg_gm_messagechat_fn),
			nullptr
		);
	}
}