#include "settings.hpp"
#include "session.hpp"
#include "hacks/anti_afk.hpp"
#include "hacks/translator.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace dino::settings
{
	namespace internal
	{
		float fps_ = 60;
		bool hacks_enabled_ = true;
		bool hacks_anti_afk_ = true;
		bool hacks_translator_ = true;

		namespace
		{
			void on_enabled_change(const events::setting_changed<hacks::is_enabled>& event)
			{
				log::info(OBFUSCATE("[on_enabled_change] is_enabled: {})"), settings::hacks::is_enabled());
				const auto state = settings::hacks::is_enabled();
			}
		}
	}

	void initialize()
	{
		static bool initialize_ = [] {
			return true;
		}();
	}

	template <auto Fn, class T>
	void modify(T&& x)
	{
		auto& dispatcher = session::dispatcher();
		if constexpr (internal::disambiguator<Fn>::setting == internal::settings::setting::fps)
		{
			log::info(OBFUSCATE("[settings] [modify] setting_changed<fps>"));
			auto event = events::setting_changed<fps>{internal::fps_};
			scheduler::enqueue(std::move(event));
			internal::fps_ = std::forward<T>(x);
			scheduler::update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::hacks_enabled)
		{
			log::info(OBFUSCATE("[settings] [modify] setting_changed<hacks::is_enabled>"));
			auto event = events::setting_changed<hacks::is_enabled>{internal::hacks_enabled_};
			scheduler::enqueue(std::move(event));
			internal::hacks_enabled_ = std::forward<T>(x);
			scheduler::update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::hacks_anti_afk)
		{
			log::info(OBFUSCATE("[settings] [modify] setting_changed<hacks::anti_afk>"));
			auto event = events::setting_changed<hacks::anti_afk>{internal::hacks_anti_afk_};
			scheduler::enqueue(std::move(event));
			internal::hacks_anti_afk_ = std::forward<T>(x);
			scheduler::update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::hacks_translator)
		{
			log::info(OBFUSCATE("[settings] [modify]setting_changed<hacks::translator>"));
			auto event = events::setting_changed<hacks::translator>{internal::hacks_translator_};
			scheduler::enqueue(std::move(event));
			internal::hacks_translator_ = std::forward<T>(x);
			scheduler::update<decltype(event)>();
		}

		else if constexpr (internal::disambiguator<Fn>::setting == internal::setting::refresh_rate)
		{
			log::info(OBFUSCATE("[settings] [modify]setting_changed<refresh_rate>"));
			auto event = events::setting_changed<refresh_rate>{internal::fps_};
			scheduler::enqueue(std::move(event));
			internal::fps_ = (1000.f / std::forward<T>(x));
			scheduler::update<decltype(event)>();
		}

		else
			static_assert(false, "[settings] [modify] Invalid setting");
	}

	void load_settings(const std::filesystem::path& path = std::filesystem::current_path())
	{
		std::ifstream file{path.string()};
		json j;
		file >> j;
	}

	std::chrono::milliseconds refresh_rate() noexcept
	{
		return std::chrono::milliseconds{static_cast<unsigned int>(1000.f / settings::fps())};
	}

	float fps() noexcept
	{
		return internal::fps_;
	}
}