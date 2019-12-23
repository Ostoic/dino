#pragma once

#include "settings_fwd.hpp"

namespace dino::internal::settings
{
	enum class setting
	{
		fps, refresh_rate,
		hacks_enabled, hacks_anti_afk, hacks_translator, hacks_cooldown_cheat
	};

	void initialize();

	template <auto Fn>
	struct disambiguator;

	template <>
	struct disambiguator<fps>
	{
		static constexpr auto setting = setting::fps;
	};

	template <>
	struct disambiguator<dino::settings::refresh_rate>
	{
		static constexpr auto setting = setting::refresh_rate;
	};

	template <>
	struct disambiguator<dino::settings::hacks::anti_afk>
	{
		static constexpr auto setting = setting::hacks_anti_afk;
	};

	template <>
	struct disambiguator<dino::settings::hacks::translator>
	{
		static constexpr auto setting = setting::hacks_translator;
	};

	template <>
	struct disambiguator<dino::settings::hacks::is_enabled>
	{
		static constexpr auto setting = setting::hacks_enabled;
	};
}
