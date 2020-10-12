#include "translator.hpp"
#include "../session.hpp"
#include "../wow/chat/language.hpp"

#include <obfuscator.hpp>

namespace dino::hacks
{
	void translator::fix_language(const events::received_chat_message& event)
	{
		event.store->set_language(wow::chat::language::common);
	}

	void translator::on_setting_change(const events::setting_changed<settings::hacks::translator>& event)
	{
		log::info(OBFUSCATE("[on_setting_change] translator: {}"), settings::hacks::translator());
		if (!settings::hacks::is_enabled() || !settings::hacks::translator())
		{
			scheduler::sink<events::received_chat_message>()
				.disconnect<fix_language>();
		}
		else
		{
			scheduler::sink<events::received_chat_message>()
				.connect<fix_language>();
		}
	}
}