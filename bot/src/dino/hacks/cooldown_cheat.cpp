#include "cooldown_cheat.hpp"
#include "../session.hpp"

#include <obfuscator.hpp>

namespace dino::hacks
{
	void cooldown_cheat::mutilate_receiver(const events::received_cooldown_cheat& event)
	{
		log::info(OBFUSCATE("[cooldown_cheat::mutilate_receiver] event: {}"), event.store->receiver());
		event.store->set_receiver(wow::guid{static_cast<std::uint64_t>(-1)});
	}

	void cooldown_cheat::on_setting_change(const events::setting_changed<settings::hacks::cooldown_cheat>& event)
	{
		log::info(OBFUSCATE("[cooldown_cheat::on_setting_change] cooldown_cheat: {}"), settings::hacks::cooldown_cheat());
		if (!settings::hacks::enabled() || !settings::hacks::cooldown_cheat())
		{
			session::get().dispatcher()
				.sink<events::received_cooldown_cheat>()
				.disconnect<mutilate_receiver>();
		}
		else
		{
			session::get().dispatcher()
				.sink<events::received_cooldown_cheat>()
				.connect<mutilate_receiver>();
		}
	}
}