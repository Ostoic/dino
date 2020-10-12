#pragma once

#include <chrono>
#include <filesystem>
#include <any>
#include <obfuscator.hpp>

#include "log.hpp"
#include "events/dino_events.hpp"
#include "settings/setting.hpp"
#include "internal/uuid.hpp"

namespace dino::settings
{
	namespace hacks
	{
		namespace mp = boost::mp11;

		//uuids
		//mp::mp_list_c<std::uint64_t, 0
		constexpr auto is_enabled_ = 0;
		constexpr auto anti_afk_ = 1;
		constexpr auto translator_ = uuid.next();
		constexpr auto uuid = uuid.next();

		inline auto is_enabled = setting{true, events::setting_changed<is_enabled_>{}};

		inline auto anti_afk = setting{true, events::setting_changed<anti_afk_>{}};

		inline auto translator = setting<events::setting_changed<uuid.next()>>{false};

	};
}
