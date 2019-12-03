#pragma once

#include "../events/chat_events.hpp"

namespace dino::emitters
{
	class chat_emitter
	{
	public:
		static chat_emitter& get() noexcept;

		static void install();
		static void uninstall();
	};
}