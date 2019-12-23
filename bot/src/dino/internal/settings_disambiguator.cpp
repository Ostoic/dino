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
	float fps_ = 60;
	bool hacks_enabled_ = true;
	bool hacks_anti_afk_ = true;
	bool hacks_translator_ = true;

	namespace
	{
		void on_enabled_change(const events::setting_changed<dino::settings::hacks::is_enabled>& event)
		{
			log::info(OBFUSCATE("[settings] [on_enabled_change] is_enabled: {})"), dino::settings::hacks::is_enabled());
			const auto state = dino::settings::hacks::is_enabled();
		}
	}

	void initialize()
	{
		namespace external = dino::settings;
		static bool initialize_ = [] {

			// hacks::translator
			dispatcher::sink<events::setting_changed<external::hacks::translator>>()
				.connect<hacks::translator::on_setting_change>();

			// hacks::is_enabled
			dispatcher::sink<events::setting_changed<external::hacks::is_enabled>>()
				.connect<on_enabled_change>();

			external::modify<external::hacks::is_enabled>(fps_);

			// hacks::anti_afk
			dispatcher::sink<events::setting_changed<external::hacks::anti_afk>>()
				.connect<hacks::anti_afk::on_setting_change>();

			external::modify<external::hacks::anti_afk>(hacks_anti_afk_);

			return true;
		}();
	}
}
