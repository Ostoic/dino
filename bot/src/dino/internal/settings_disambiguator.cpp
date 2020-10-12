#include "settings_disambiguator.hpp"
#include "settings_fwd.hpp"

#include <obfuscator.hpp>

#include "../log.hpp"
#include "../events/dino_events.hpp"
#include "../settings.hpp"

#include "../hacks/anti_afk.hpp"
#include "../hacks/translator.hpp"

namespace dino::internal::settings
{
	namespace
	{
		void on_enabled_change(const events::setting_changed<dino::settings::hacks::is_enabled>& event)
		{
			log::info(OBFUSCATE("[settings] [on_enabled_change] is_enabled: {})"), dino::settings::hacks::is_enabled());
			const auto state = dino::settings::hacks::is_enabled();
		}
	}
}
