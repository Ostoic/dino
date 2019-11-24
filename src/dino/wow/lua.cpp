#include "lua.hpp"

#include "../session.hpp"

#include "../wow/console.hpp"

namespace dino::wow::lua
{
	void run(const std::string& script)
	{
		session::get().queue_task([&] {
			wow::console::write("[dino] Lua script: " + script);
		});
	}

}