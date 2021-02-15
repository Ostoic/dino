#include "hacks_emitter.hpp"
#include "emitters.hpp"

#include "../events/dino_events.hpp"
#include "../scheduler.hpp"
#include "../log.hpp"
#include "../session.hpp"
#include "../settings.hpp"
#include "../hacks/anti_afk.hpp"
#include "../hacks/translator.hpp"

namespace dino::emitters
{
	void hacks_emitter::install()
	{
		scheduler::sink<events::setting_changed>()
			.connect<hacks::anti_afk::on_setting_change>();

		scheduler::sink<events::setting_changed>()
			.connect<hacks::translator::on_setting_change>();

		auto& settings = session::settings();
		settings.set("hacks.is_enabled", true);
		settings.set("hacks.anti_afk", true);
		settings.set("hacks.translator", true);
		log::info(OBFUSCATE("[hacks_emitter] installed"));
	}

	void hacks_emitter::uninstall()
	{
		scheduler::sink<events::setting_changed>()
			.disconnect<hacks::anti_afk::on_setting_change>();

		scheduler::sink<events::setting_changed>()
			.disconnect<hacks::translator::on_setting_change>();

		auto& settings = session::settings();
		settings.set("hacks.translator", false);
		settings.set("hacks.anti_afk", false);
		settings.set("hacks.is_enabled", false);
		log::info(OBFUSCATE("[hacks_emitter] uninstalled"));
	}
}