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

	void anti_afk::on_setting_change(const events::setting_changed& event)
	{
		if (event.setting_name != "hacks.anti_afk")
			return;

		const auto& settings = session::settings();
		log::info(OBFUSCATE("[on_setting_change] anti_afk: {}"), settings.lookup<bool>(event.setting_name));
		if (!settings.lookup<bool>("hacks.is_enabled") || !settings.lookup<bool>(event.setting_name))
		{
			scheduler::sink<events::endscene_frame>()
				.disconnect<tick>();
		}
		else
		{
			scheduler::sink<events::endscene_frame>()
				.connect<tick>();
		}
	}
}