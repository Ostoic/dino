#pragma once

#include "../offset.hpp"

#include <chrono>
#include <queue>
#include <mutex>
#include <thread>
#include <functional>

namespace dino::emitters
{
	class endscene_emitter
	{
	private:
		using clock = std::chrono::high_resolution_clock;

	public:
		static void install();
		static void uninstall();

		static endscene_emitter& get() noexcept;

	public:
		bool is_active() const;

		std::chrono::nanoseconds last_hook_runtime() const;

	private:
		static unsigned int original_endscene;

		endscene_emitter();

		void hook();
		void unhook();

	private:
		friend class session;
		friend class command_handler;
		friend void endscene_hook();

	private:
		std::mutex tasks_mutex_;
		clock::time_point last_frame_time_;
		std::chrono::nanoseconds last_hook_runtime_;
	};
}
