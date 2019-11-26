#include "debug.hpp"

#include "wow/console.hpp"
#include "session.hpp"

namespace dino
{
	void debug(const std::string& module_name)
	{
		using namespace std::chrono_literals;
		//dino::allocate_console();
		wow::console::enable();
		wow::console::open();
		session::start();
	}

	void allocate_console()
	{
		if (::AllocConsole())
		{
			freopen("CONOUT$", "w", stderr);
			freopen("CONOUT$", "w", stdout);
			freopen("CONIN$", "r", stdin);
		}

		spdlog::info("[dino] Console allocated");
	}
}