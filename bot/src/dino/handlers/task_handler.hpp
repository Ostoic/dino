#pragma once

#include "../offset.hpp"
#include "../events/endscene_events.hpp"

#include <chrono>
#include <queue>
#include <mutex>
#include <thread>
#include <functional>

namespace dino::handlers
{
	class task_handler
	{
	private:
		using clock = std::chrono::high_resolution_clock;

	public:
		static task_handler& get() noexcept;

		static void handle(const events::endscene_frame& event);

		template <class Fn>
		static bool queue_task(Fn&& fn);

		template <class Duration, class Fn>
		static bool queue_async_task(Duration duration, Fn&& fn);

		template <class Fn>
		static bool queue_async_task(Fn&& fn);

	private:
		std::queue<std::function<void()>> tasks_;
		std::timed_mutex mutex_;
	};
}

namespace dino::handlers
{
	template <class Fn>
	bool task_handler::queue_task(Fn&& fn)
	{
		using namespace std::chrono_literals;
		auto& handler = task_handler::get();
		//auto lock = std::unique_lock{handler.mutex_};
		//if (!lock.try_lock_for(100ms))
		//	return false;

		handler.tasks_.emplace(std::forward<Fn>(fn));
		return true;
	}

	template <class Duration, class Fn>
	bool task_handler::queue_async_task(Duration duration, Fn&& fn)
	{
		return queue_task([&fn, duration] {
			std::thread{[&] {
				std::this_thread::sleep_for(duration);
				std::forward<Fn>(fn)();
			}}.detach();
		});
	}

	template <class Fn>
	bool task_handler::queue_async_task(Fn&& fn)
	{
		return queue_task([&fn] {
			std::thread{[] {
				std::forward<Fn>(fn)();
			}}.detach();
		});
	}
}