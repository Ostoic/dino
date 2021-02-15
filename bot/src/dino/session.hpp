#pragma once

#include <chrono>
#include <vector>
#include <entt/entt.hpp>
#include <spdlog/sinks/basic_file_sink.h>

#include "settings.hpp"
#include "emitters/endscene_emitter.hpp"
#include "offset.hpp"
#include "scheduler.hpp"

namespace dino
{
	class session
	{
		using settings_t = settings;
	public:
		static void start();
		static void exit();

		using clock = std::chrono::high_resolution_clock;

	public:
		static std::string identity();
		static std::string context();
		static std::string status();

	public:
		static settings_t& settings() noexcept;

		static entt::registry& registry() noexcept;
		static scheduler& dispatcher() noexcept;

		static std::string status_message();

		template <class... Args>
		static bool run_script(Args&&... args);

	private:
		friend class emitters::endscene_emitter;

		static session& get();

	private:
		entt::registry registry_;
		settings_t settings_;
	};
}