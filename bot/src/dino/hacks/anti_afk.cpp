#include "anti_afk.hpp"

#include "../wow/console.hpp"

namespace dino::hacks::anti_afk
{
	void tick(const events::endscene_frame& event)
	{
		unsigned int& last_action = deref_as<unsigned int>(wow::offsets::time::last_action);
		unsigned int timestamp = deref_as<unsigned int>(wow::offsets::time::timestamp);
		last_action = timestamp;
	}
}