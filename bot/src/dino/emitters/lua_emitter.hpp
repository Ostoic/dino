#pragma once

#include "../events/chat_events.hpp"
#include "../wow/framexml/events.hpp"
#include "../session.hpp"
#include "../wow/lua.hpp"

#include <obfuscator.hpp>

namespace dino::emitters
{
	class lua_emitter
	{
	public:
		static void install();
		static void uninstall();

		template <class Event, auto Fn>
		static void emit_on(const wow::framexml::event event, const std::string& name)
		{
			wow::lua::run(
				OBFUSCATE("dino.internals.register('{}', '{}', function(args) dino_action = 'event.emit' dino_action_data = args end)"),
				name, to_string(event)
			);

			scheduler::sink<Event>()
				.connect<Fn>();
		}

	public:
	};
}