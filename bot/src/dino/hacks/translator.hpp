#pragma once

#include "../events/chat_events.hpp"

namespace dino::hacks::translator
{
	void fix_language(const events::new_chat_message& event);
}