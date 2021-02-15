#include "settings_emitter.hpp"
#include "emitters.hpp"

#include "../events/dino_events.hpp"
#include "../scheduler.hpp"
#include "../log.hpp"
#include "../session.hpp"
#include "../settings.hpp"

namespace dino::emitters
{
	void dispatch_setting_handlers(const events::setting_changed& event)
	{
		auto& settings = session::settings();
		if (!settings.contains(event.setting_name))
			settings.set(event.setting_name, event.prev);
	}

	void settings_emitter::install()
	{
		auto& settings = session::settings();
		scheduler::sink<events::setting_changed>()
			.connect<dispatch_setting_handlers>();

		settings.set("fps", 60);
		settings.set("refresh_rate", std::chrono::milliseconds{static_cast<long>(1000/60)});

		log::info(OBFUSCATE("[settings_emitter] installed"));
	}

	void settings_emitter::uninstall()
	{
		scheduler::sink<events::setting_changed>()
			.disconnect<dispatch_setting_handlers>();

		log::info(OBFUSCATE("[settings_emitter] uninstalled"));
	}
}