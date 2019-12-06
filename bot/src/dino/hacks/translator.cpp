#include "translator.hpp"
#include "../session.hpp"

#include <obfuscator.hpp>

namespace dino::hacks
{
	void translator::fix_language(const events::received_chat_message& event)
	{
		event.message->set_language(0);
	}

	void translator::on_setting_change(const events::setting_changed<settings::hacks::translator>& event)
	{
		log::info(OBFUSCATE("[on_setting_change] translator: {}"), settings::hacks::translator());
		if (!settings::hacks::enabled() || !settings::hacks::translator())
		{
			session::dispatcher()
				.sink<events::received_chat_message>()
				.disconnect<fix_language>();
		}
		else
		{
			session::dispatcher()
				.sink<events::received_chat_message>()
				.connect<fix_language>();
		}
	}
}