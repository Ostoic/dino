#include "translator.hpp"

#include "../wow/console.hpp"

namespace dino::hacks::translator
{
	void fix_language(const events::new_chat_message& event)
	{
		event.message->set_language(0);
	}
}