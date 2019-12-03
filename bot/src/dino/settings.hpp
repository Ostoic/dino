#pragma once

#include <chrono>
#include <filesystem>

namespace dino
{
	class settings
	{
	public:
		static settings& get() noexcept;

		struct hacks
		{
			static bool anti_afk() noexcept;
			static bool translator() noexcept;
		};

	public:
		static std::chrono::milliseconds refresh_rate() noexcept;
		static float fps() noexcept;

	private:
		settings();

	private:
		friend void load_settings(const std::filesystem::path& path);
		float fps_ = 60;
		bool hacks_anti_afk_ = true;
		bool hacks_translator_ = true;
	};
}
