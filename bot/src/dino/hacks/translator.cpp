#include "translator.hpp"
#include "../session.hpp"
#include "../wow/chat/language.hpp"

#include <obfuscator.hpp>

namespace dino::hacks
{
	void translator::fix_language(const events::received_chat_message& event)
	{
		switch (event.store->msg_type())
		{
		case wow::chat::message::type::say:
		case wow::chat::message::type::yell:
		case wow::chat::message::type::text_emote:
		case wow::chat::message::type::emote:
			break;
		default:
			return;
		}

		log::debug(OBFUSCATE("[translator::fix_language] message language: {}"), event.store->language());
		event.store->set_language(wow::chat::language::common);
	}

	void translator::on_setting_change(const events::setting_changed& event)
	{
		if (event.setting_name != "hacks.translator")
			return;

		const auto& settings = session::settings();
		log::info(OBFUSCATE("[on_setting_change] translator: {}"), settings.lookup<bool>(event.setting_name));
		if (!settings.lookup<bool>("hacks.is_enabled") || !settings.lookup<bool>(event.setting_name))
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