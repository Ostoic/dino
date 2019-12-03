#include "debug.hpp"

#include "wow/console.hpp"
#include "session.hpp"

namespace dino::debug
{
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

	void delete_console()
	{
		spdlog::info("[dino] Freeing console");
		::FreeConsole();
	}
}