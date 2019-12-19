#pragma once

#include "../offset.hpp"
#include "../events/endscene_events.hpp"

#include <chrono>
#include <queue>
#include <mutex>
#include <thread>
#include <functional>

#include "../log.hpp"

namespace dino { class session; }

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

		enum class transient_state
		{
			pass, disconnect
		};

	private:
		friend class dino::session;

		template <class Event>
		static std::queue<std::function<transient_state(const Event&)>>& transients();

	private:
		std::queue<std::function<void()>> tasks_;
		//std::timed_mutex mutex_;
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

		log::info("task_handler::queue_task");
		handler.tasks_.emplace(std::forward<Fn>(fn));
		return true;
	}

	template <class Duration, class Fn>
	bool task_handler::queue_async_task(Duration duration, Fn&& fn)
	{
		log::info("task_handler::queue_async_task");
		std::thread{[&] {
			log::info("inside new thread!");
			std::this_thread::sleep_for(duration);
			task_handler::queue_task(std::forward<Fn>(fn));
		}}.detach();
		return true;
	}

	template <class Fn>
	bool task_handler::queue_async_task(Fn&& fn)
	{
		log::info("task_handler::queue_async_task");
		std::thread{[&] {
			log::info("inside new thread!");
			task_handler::queue_task(std::forward<Fn>(fn));
			log::info("after in thread!");
		}}.detach();
		return true;
	}

	template <class Event>
	static std::queue<std::function<task_handler::transient_state(const Event&)>>& task_handler::transients()
	{
		static std::queue<std::function<task_handler::transient_state(const Event&)>> transients_;
		return transients_;
	}
}