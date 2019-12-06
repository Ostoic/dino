#include "gamestate_handler.hpp"

#include "../emitters/lua_emitter.hpp"
#include "../log.hpp"

#include <obfuscator.hpp>

namespace dino::handlers
{
	void reinstall_lua_emitter(const events::gamestate_change& event)
	{
		constexpr auto either_ingame = [](const auto& left, const auto& right)
		{
			return left == wow::glue::screen::ingame || right == wow::glue::screen::ingame;
		};

		if (either_ingame(event.before, event.after) || event.before == event.after)
		{
			log::info(OBFUSCATE("[reinstall_lua_emitter] reinstalling lua_emitter..."));
			emitters::lua_emitter::uninstall();
			emitters::lua_emitter::install();
		}
	}
}