#include "settings.hpp"
#include "session.hpp"
#include "hacks/anti_afk.hpp"
#include "hacks/translator.hpp"
#include "hacks/cooldown_cheat.hpp"

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
		bool hacks_cooldown_cheat_ = true;

		namespace
		{
			void on_enabled_change(const events::setting_changed<hacks::enabled>& event)
			{
				log::info(OBFUSCATE("[on_enabled_change] enabled: {})"), settings::hacks::enabled());
				const auto state = settings::hacks::enabled();
			}
		}

		void initialize()
		{
			static bool initialize_ = [] {
				auto& dispatcher = session::dispatcher();
				dispatcher
					.sink<events::setting_changed<hacks::anti_afk>>()
					.connect<dino::hacks::anti_afk::on_setting_change>();

				dispatcher
					.sink<events::setting_changed<hacks::translator>>()
					.connect<dino::hacks::translator::on_setting_change>();

				dispatcher
					.sink<events::setting_changed<hacks::cooldown_cheat>>()
					.connect<dino::hacks::cooldown_cheat::on_setting_change>();

				dispatcher
					.sink<events::setting_changed<hacks::enabled>>()
					.connect<on_enabled_change>();

				settings::modify<fps>(fps());
				settings::modify<hacks::enabled>(hacks::enabled());
				settings::modify<hacks::anti_afk>(hacks::anti_afk());
				settings::modify<hacks::translator>(hacks::translator());
				settings::modify<hacks::cooldown_cheat>(hacks::cooldown_cheat());
				return true;
			}();

			static_cast<void>(initialize);
		}
	}

	namespace hacks
	{
		bool anti_afk() noexcept
		{
			return internal::hacks_anti_afk_;
		}

		bool enabled() noexcept
		{
			return internal::hacks_enabled_;
		}

		bool translator() noexcept
		{
			return internal::hacks_translator_;
		}

		bool cooldown_cheat() noexcept
		{
			return internal::hacks_cooldown_cheat_;
		}
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