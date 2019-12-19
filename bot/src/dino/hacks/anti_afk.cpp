#include "anti_afk.hpp"
#include "../session.hpp"
#include "../log.hpp"
#include "../wow/world/time.hpp"

#include <obfuscator.hpp>

namespace dino::hacks
{
	void anti_afk::tick(const events::endscene_frame& event)
	{
		const auto timestamp = wow::world::timestamp();
		wow::world::set_last_action_time(timestamp);
	}

	void anti_afk::on_setting_change(const events::setting_changed<settings::hacks::anti_afk>& event)
	{
		log::info(OBFUSCATE("[on_setting_change] anti_afk: {}"), settings::hacks::anti_afk());
		if (!settings::hacks::enabled() || !settings::hacks::anti_afk())
		{
			dispatcher::sink<events::endscene_frame>()
				.disconnect<tick>();
		}
		else
		{
			dispatcher::sink<events::endscene_frame>()
				.connect<tick>();
		}
	}
}