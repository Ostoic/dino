#pragma once

#include "../offset.hpp"

#include <chrono>
#include <queue>
#include <mutex>
#include <thread>
#include <functional>

namespace dino::handlers
{
	class task_handler
	{
	public:
		struct service
		{
			std::string name;
			std::function<void()> fn;
		};

	private:
		using clock = std::chrono::high_resolution_clock;

	public:
		static void install_hook();
		static void uninstall_hook();

		static task_handler& get() noexcept;

	public:
		bool is_active() const;

		template <class Fn>
		bool queue_task(Fn&& fn)
		{
			if (!this->is_active())
				return false;

			auto lock = std::unique_lock<std::mutex>{tasks_mutex_};
			if (lock.owns_lock())
			{
				tasks_.push(std::function<void()>{std::forward<Fn>(fn)});
				return true;
			}

			return false;
		}

		template <class Duration, class Fn>
		bool queue_async_task(Duration duration, Fn&& fn)
		{
			return queue_task([&fn, duration] {
				std::thread{[&fn, duration] {
					std::this_thread::sleep_for(duration);
					std::forward<Fn>(fn)();
				}}.detach();
			});
		}

		template <class Fn>
		bool queue_async_task(Fn&& fn)
		{
			return queue_task([&fn] {
				std::thread{std::forward<Fn>(fn)}.detach();
			});
		}
	private:
		template <class Fn>
		bool add_service(std::string name, Fn&& fn);

		bool remove_service(std::string name);

	private:
		static unsigned int original_endscene;

		task_handler();

		void hook();
		void unhook();

		static void update_session();

	private:
		friend class session;
		friend class command_handler;
		friend void endscene_hook();

	private:
		std::mutex tasks_mutex_;
		std::queue<std::function<void()>> tasks_;
		std::vector<service> services_;
		clock::time_point last_frame_time_;
	};
}
