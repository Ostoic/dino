#pragma once

#include "../events/dino_events.hpp"
#include "../events/world_events.hpp"
#include "../settings.hpp"

namespace dino::hacks
{
	struct cooldown_cheat
	{
		static void mutilate_receiver(const events::received_cooldown_cheat& event);
		static void on_setting_change(const events::setting_changed<settings::hacks::cooldown_cheat>& event);
	};
}
