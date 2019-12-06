#include "chat_emitter.hpp"
#include "emitters.hpp"

#include "../events/chat_events.hpp"
#include "../log.hpp"

#include <obfuscator.hpp>

namespace dino::emitters
{
	void chat_emitter::install()
	{
		emitters::make_net_emitter<events::received_chat_message>();
		emitters::make_net_emitter<events::received_gm_chat_message>();
		emitters::make_net_emitter<events::received_text_emote>();

		log::info(OBFUSCATE("[chat_emitter] installed emitters"));
	}

	void chat_emitter::uninstall()
	{
		emitters::restore_net_emitter<events::received_chat_message>();
		emitters::restore_net_emitter<events::received_gm_chat_message>();
		emitters::restore_net_emitter<events::received_text_emote>();

		log::info(OBFUSCATE("[chat_emitter] uninstalled emitters"));
	}
}