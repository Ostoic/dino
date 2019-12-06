#pragma once

#include "../events/endscene_events.hpp"
#include "../events/dino_events.hpp"
#include "../settings.hpp"

namespace dino::hacks
{
	struct anti_afk
	{
		static void tick(const events::endscene_frame& event);
		static void on_setting_change(const events::setting_changed<settings::hacks::anti_afk>& event);
	};
}
