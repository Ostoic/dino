#pragma once

#include "../events/chat_events.hpp"
#include "../wow/framexml/events.hpp"
#include "../session.hpp"

#include <obfuscator.hpp>

namespace dino::emitters
{
	class net_emitter
	{
	public:
		static void install();
		static void uninstall();
	};
}