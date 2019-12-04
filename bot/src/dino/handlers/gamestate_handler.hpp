#pragma once

#include "../events/glue_events.hpp"

namespace dino::handlers
{
	void reinstall_lua_emitter(const events::gamestate_change& event);
}
