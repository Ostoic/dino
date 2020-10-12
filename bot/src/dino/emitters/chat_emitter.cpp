#include "chat_emitter.hpp"
#include "emitters.hpp"

#include "../events/chat_events.hpp"
#include "../scheduler.hpp"
#include "../log.hpp"

#include <obfuscator.hpp>

namespace dino::emitters
{
	namespace
	{
		template <class ChatEvent>
		void log_chat(const ChatEvent& event)
		{
			log::info("cursor = {}", event.store->cursor());
			const auto text = event.store->text();
			const auto sender = event.store->sender();

			log::info(
				OBFUSCATE("[chat_emitter] [{}] [{}]: {}"),
				to_string_view(event.store->msg_type()),
				sender,
				text
			);
			event.store->restore_cursor();
		}

		void log_text_emote(const events::received_text_emote& event)
		{
			const auto guid = event.store->pull<wow::guid>();
			const auto emote_id = event.store->pull<unsigned int>();
			event.store->pull<unsigned int>();

			const auto max_length = event.store->pull<unsigned int>();
			const auto target_player_name = event.store->pull<const char*>(max_length);
			log::info(
				OBFUSCATE("[chat_emitter] [emote]: {} {} {}"),
				guid, emote_id, target_player_name
			);
			event.store->restore_cursor();
		}
	}

	void chat_emitter::install()
	{
		// Enable chat logging
		scheduler::sink<events::received_chat_message>()
			.connect<log_chat<events::received_chat_message>>();

		scheduler::sink<events::received_gm_chat_message>()
			.connect<log_chat<events::received_gm_chat_message>>();

		// Enable emote logging
		scheduler::sink<events::received_text_emote>()
			.connect<log_text_emote>();

		emitters::make_net_emitter<events::received_chat_message>();
		emitters::make_net_emitter<events::received_gm_chat_message>();
		emitters::make_net_emitter<events::received_text_emote>();
		log::info(OBFUSCATE("[chat_emitter] installed"));
	}

	void chat_emitter::uninstall()
	{
		// Disable chat logging
		scheduler::sink<events::received_chat_message>()
			.disconnect<log_chat<events::received_chat_message>>();

		scheduler::sink<events::received_gm_chat_message>()
			.disconnect<log_chat<events::received_gm_chat_message>>();

		// Disable emote logging
		scheduler::sink<events::received_text_emote>()
			.disconnect<log_text_emote>();

		emitters::restore_net_emitter<events::received_chat_message>();
		emitters::restore_net_emitter<events::received_gm_chat_message>();
		emitters::restore_net_emitter<events::received_text_emote>();
		log::info(OBFUSCATE("[chat_emitter] uninstalled"));
	}
}