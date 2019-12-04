#include "events.hpp"

#include <iostream>

namespace dino::wow::framexml
{
	std::string to_string(const event event)
	{
		switch (event)
		{
			case event::unit_pet: return "UNIT_PET";
			case event::unit_pet2: return "UNIT_PET2";
			case event::unit_target: return "UNIT_TARGET";
			case event::unit_display_power: return "UNIT_DISPLAY_POWER";
			case event::unit_health: return "UNIT_HEALTH";
			case event::unit_mana: return "UNIT_RAGE";
			case event::unit_rage: return "UNIT_MANA";
			case event::unit_focus: return "UNIT_FOCUS";
			case event::unit_energy: return "UNIT_ENERGY";
			case event::unit_happiness: return "UNIT_HAPPINESS";
			case event::unit_runic_power: return "UNIT_RUNIC_POWER";
			case event::unit_max_health: return "UNIT_MAXHEALTH";
			case event::unit_max_mana: return "UNIT_MAXMANA";

			case event::player_target_changed: return "PLAYER_TARGET_CHANGED";

			case event::system_message: return "SYSMSG";

			case event::ui_error_message: return "UI_ERROR_MESSAGE";
			case event::ui_info_message: return "UI_INFO_MESSAGE";

			case event::player_login: return "PLAYER_LOGIN";
			case event::player_logout: return "PLAYER_LOGOUT";
			case event::player_entering_world: return "PLAYER_ENTERING_WORLD";
			case event::player_leaving_world: return "PLAYER_LEAVING_WORLD";
			case event::player_alive: return "PLAYER_ALIVE";
			case event::player_dead: return "PLAYER_DEAD";
			case event::player_camping: return "PLAYER_CAMPING";
			case event::player_qutting: return "PLAYER_QUITTING";
			case event::logout_cancel: return "LOGOUT_CANCEL";
			case event::resurrect_request: return "RESURRECT_REQUEST";
		}

		return {};
	}

	event to_event(std::string text)
	{
		if (text == "UNIT_PET") return event::unit_pet;
		else if (text == "UNIT_PET2") return event::unit_pet2;
		else if (text == "UNIT_TARGET") return event::unit_target;
		else if (text == "UNIT_DISPLAY_POWER") return event::unit_display_power;
		else if (text == "UNIT_HEALTH") return event::unit_health;
		else if (text == "UNIT_RAGE") return event::unit_mana;
		else if (text == "UNIT_MANA") return event::unit_rage;
		else if (text == "UNIT_FOCUS") return event::unit_focus;
		else if (text == "UNIT_ENERGY") return event::unit_energy;
		else if (text == "UNIT_HAPPINESS") return event::unit_happiness;
		else if (text == "UNIT_RUNIC_POWER") return event::unit_runic_power;
		else if (text == "UNIT_MAXHEALTH") return event::unit_max_health;
		else if (text == "UNIT_MAXMANA") return event::unit_max_mana;

		else if (text == "PLAYER_TARGET_CHANGED") return event::player_target_changed;

		else if (text == "SYSMSG") return event::system_message;

		else if (text == "UI_ERROR_MESSAGE") return event::ui_error_message;
		else if (text == "UI_INFO_MESSAGE") return event::ui_info_message;

		else if (text == "PLAYER_LOGIN") return event::player_login;
		else if (text == "PLAYER_LOGOUT") return event::player_logout;
		else if (text == "PLAYER_ENTERING_WORLD") return event::player_entering_world;
		else if (text == "PLAYER_LEAVING_WORLD") return event::player_leaving_world;
		else if (text == "PLAYER_ALIVE") return event::player_alive;
		else if (text == "PLAYER_DEAD") return event::player_dead;
		else if (text == "PLAYER_CAMPING") return event::player_camping;
		else if (text == "PLAYER_QUITTING") return event::player_qutting;
		else if (text == "LOGOUT_CANCEL") return event::logout_cancel;
		else if (text == "RESURRECT_REQUEST") return event::resurrect_request;

		return {};
	}

}
