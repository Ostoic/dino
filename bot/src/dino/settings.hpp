#pragma once

#include <chrono>
#include <filesystem>
#include <obfuscator.hpp>

#include "log.hpp"
#include "dispatcher.hpp"

#include "events/dino_events.hpp"

#include "internal/settings_disambiguator.hpp"

namespace dino::settings
{
	// Idea:
	// Idea setting class:
	// fn call operator(): so that we access settings through global inline function objects
	//		keeps the same interface while making setting creation simpler.
	// default_value: for use with internal::settings::initialize.
	//
	// Also consider making it so that we can make new settings at runtime, etc (virtual)
	// Idea:

	// settings::fps() -> read fps
	// settings::fps.read() -> read fps?
	// settings::modify<settings::fps>()

	namespace hacks
	{
		bool is_enabled() noexcept;
		bool anti_afk() noexcept;
		bool translator() noexcept;
	};

	std::chrono::milliseconds refresh_rate() noexcept;
	float fps() noexcept;

	template <auto Fn, class T>
	void modify(T&& x)
	{
		auto& dispatcher = session::dispatcher();
		if constexpr (internal::disambiguator<Fn>::setting == internal::settings::setting::fps)
		{
			log::info(OBFUSCATE("[settings] [modify] setting_changed<fps>"));
			auto event = events::setting_changed<fps>{internal::fps_};
			dispatcher::enqueue(std::move(event));
			internal::fps_ = std::forward<T>(x);
			dispatcher::update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::hacks_enabled)
		{
			log::info(OBFUSCATE("[settings] [modify] setting_changed<hacks::is_enabled>"));
			auto event = events::setting_changed<hacks::is_enabled>{internal::hacks_enabled_};
			dispatcher::enqueue(std::move(event));
			internal::hacks_enabled_ = std::forward<T>(x);
			dispatcher::update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::hacks_anti_afk)
		{
			log::info(OBFUSCATE("[settings] [modify] setting_changed<hacks::anti_afk>"));
			auto event = events::setting_changed<hacks::anti_afk>{internal::hacks_anti_afk_};
			dispatcher::enqueue(std::move(event));
			internal::hacks_anti_afk_ = std::forward<T>(x);
			dispatcher::update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::hacks_translator)
		{
			log::info(OBFUSCATE("[settings] [modify]setting_changed<hacks::translator>"));
			auto event = events::setting_changed<hacks::translator>{internal::hacks_translator_};
			dispatcher::enqueue(std::move(event));
			internal::hacks_translator_ = std::forward<T>(x);
			dispatcher::update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::refresh_rate)
		{
			log::info(OBFUSCATE("[settings] [modify]setting_changed<refresh_rate>"));
			auto event = events::setting_changed<refresh_rate>{internal::fps_};
			dispatcher::enqueue(std::move(event));
			internal::fps_ = (1000.f / std::forward<T>(x));
			dispatcher::update<decltype(event)>();
		}

		else
			static_assert(false, "[settings] [modify] Invalid setting");
	}
}
