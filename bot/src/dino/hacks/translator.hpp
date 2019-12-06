#pragma once

#include "../events/chat_events.hpp"
#include "../events/dino_events.hpp"
#include "../settings.hpp"

namespace dino::hacks
{
	struct translator
	{
		static void fix_language(const events::received_chat_message& event);
		static void on_setting_change(const events::setting_changed<settings::hacks::translator>& event);
	};
}
