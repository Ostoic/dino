#include "debug.hpp"

#include "session.hpp"
#include "log.hpp"

#include <obfuscator.hpp>

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

		log::info(OBFUSCATE("[dino] Console allocated"));
	}

	void delete_console()
	{
		::FreeConsole();
		log::info(OBFUSCATE("[dino] Freed console"));
	}
}