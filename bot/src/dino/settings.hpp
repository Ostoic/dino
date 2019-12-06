#pragma once

#include <chrono>
#include <filesystem>

#include <obfuscator.hpp>

#include "log.hpp"
#include "session.hpp"
#include "events/dino_events.hpp"

namespace dino::settings
{
	namespace internal
	{
		enum class setting
		{
			fps, refresh_rate,
			hacks_enabled, hacks_anti_afk, hacks_translator, hacks_cooldown_cheat
		};

		extern float fps_;
		extern bool hacks_enabled_;
		extern bool hacks_anti_afk_;
		extern bool hacks_translator_;
		extern bool hacks_cooldown_cheat_;

		void initialize();
	}

	namespace hacks
	{
		bool enabled() noexcept;
		bool anti_afk() noexcept;
		bool translator() noexcept;
		bool cooldown_cheat() noexcept;
	};

	std::chrono::milliseconds refresh_rate() noexcept;
	float fps() noexcept;

	namespace internal
	{
		template <auto Fn>
		struct disambiguator;

		template <>
		struct disambiguator<fps>
		{
			static constexpr auto setting = internal::setting::fps;
		};

		template <>
		struct disambiguator<refresh_rate>
		{
			static constexpr auto setting = internal::setting::refresh_rate;
		};

		template <>
		struct disambiguator<hacks::anti_afk>
		{
			static constexpr auto setting = internal::setting::hacks_anti_afk;
		};

		template <>
		struct disambiguator<hacks::translator>
		{
			static constexpr auto setting = internal::setting::hacks_translator;
		};

		template <>
		struct disambiguator<hacks::cooldown_cheat>
		{
			static constexpr auto setting = internal::setting::hacks_cooldown_cheat;
		};

		template <>
		struct disambiguator<hacks::enabled>
		{
			static constexpr auto setting = internal::setting::hacks_enabled;
		};
	}

	template <auto Fn, class T>
	void modify(T&& x)
	{
		auto& dispatcher = session::get().dispatcher();
		if constexpr (internal::disambiguator<Fn>::setting == internal::setting::fps)
		{
			log::info(OBFUSCATE("[settings::modify] emit: events::setting_changed<fps>"));
			auto event = events::setting_changed<fps>{internal::fps_};
			dispatcher.enqueue(std::move(event));
			internal::fps_ = std::forward<T>(x);
			dispatcher.update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::hacks_enabled)
		{
			log::info(OBFUSCATE("[settings::modify] emit: events::setting_changed<hacks::enabled>"));
			auto event = events::setting_changed<hacks::enabled>{internal::hacks_enabled_};
			dispatcher.enqueue(std::move(event));
			internal::hacks_enabled_ = std::forward<T>(x);
			dispatcher.update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::hacks_anti_afk)
		{
			log::info(OBFUSCATE("[settings::modify] emit: events::setting_changed<hacks::anti_afk>"));
			auto event = events::setting_changed<hacks::anti_afk>{internal::hacks_anti_afk_};
			dispatcher.enqueue(std::move(event));
			internal::hacks_anti_afk_ = std::forward<T>(x);
			dispatcher.update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::hacks_translator)
		{
			log::info(OBFUSCATE("[settings::modify] emit: events::setting_changed<hacks::translator>"));
			auto event = events::setting_changed<hacks::translator>{internal::hacks_translator_};
			dispatcher.enqueue(std::move(event));
			internal::hacks_translator_ = std::forward<T>(x);
			dispatcher.update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::hacks_cooldown_cheat)
		{
			log::info(OBFUSCATE("[settings::modify] emit: events::setting_changed<hacks::cooldown_cheat>"));
			auto event = events::setting_changed<hacks::cooldown_cheat>{internal::hacks_cooldown_cheat_};
			dispatcher.enqueue(std::move(event));
			internal::hacks_cooldown_cheat_ = std::forward<T>(x);
			dispatcher.update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::refresh_rate)
		{
			log::info(OBFUSCATE("[settings::modify] emit: events::setting_changed<refresh_rate>"));
			auto event = events::setting_changed<refresh_rate>{internal::fps_};
			dispatcher.enqueue(std::move(event));
			internal::fps_ = (1000.f / std::forward<T>(x));
			dispatcher.update<decltype(event)>();
		}

		else
			static_assert(false, "[setting::modify] Invalid setting");
	}
}
