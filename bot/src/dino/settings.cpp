#include "settings.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace dino
{
	void load_settings(const std::filesystem::path& path = std::filesystem::current_path())
	{
		auto& settings = settings::get();
		std::ifstream file{path.string()};
		json j;
		file >> j;
	}

	settings& settings::get() noexcept
	{
		static settings me;
		return me;
	}

	std::chrono::milliseconds settings::refresh_rate() noexcept
	{
		return std::chrono::milliseconds{static_cast<unsigned int>(1000.f / settings::fps())};
	}

	std::string settings::json_library_path()
	{
		return get().json_library_path_;
	}

	float settings::fps() noexcept
	{
		return get().fps_;
	}

	bool settings::hacks::anti_afk() noexcept
	{
		return get().hacks_anti_afk_;
	}

	bool settings::hacks::enabled() noexcept
	{
		return get().hacks_enabled_;
	}

	bool settings::hacks::translator() noexcept
	{
		return get().hacks_translator_;
	}

	settings::settings()
	{
		//load_settings();
	}
}