#include "anti_afk.hpp"
#include "../session.hpp"
#include "../log.hpp"

#include <obfuscator.hpp>

namespace dino::hacks
{
	void anti_afk::tick(const events::endscene_frame& event)
	{
		unsigned int& last_action = deref_as<unsigned int>(wow::offsets::time::last_action);
		unsigned int timestamp = deref_as<unsigned int>(wow::offsets::time::timestamp);
		last_action = timestamp;
	}

	void anti_afk::on_setting_change(const events::setting_changed<settings::hacks::anti_afk>& event)
	{
		log::info(OBFUSCATE("[on_setting_change] anti_afk: {}"), settings::hacks::anti_afk());
		if (!settings::hacks::enabled() || !settings::hacks::anti_afk())
		{
			session::dispatcher()
				.sink<events::endscene_frame>()
				.disconnect<tick>();
		}
		else
		{
			session::dispatcher()
				.sink<events::endscene_frame>()
				.connect<tick>();
		}
	}
}