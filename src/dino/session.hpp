#pragma once

#include <chrono>
#include <entt/entt.hpp>

#include "handlers/task_handler.hpp"

namespace dino
{
	namespace handlers { class task_handler; }

	class session
	{
	public:
		static session& start();
		static session& get();

		using clock = std::chrono::high_resolution_clock;

	public:
		entt::registry& registry() noexcept;
		entt::dispatcher& dispatcher() noexcept;

		template <class Fn>
		bool queue_task(Fn&& fn)
		{
			auto& task_handler = handlers::task_handler::get();
			return task_handler.queue_task(std::forward<Fn>(fn));
		}

		template <class Duration, class Fn>
		bool queue_async_task(Duration duration, Fn&& fn)
		{
			auto& task_handler = handlers::task_handler::get();
			return task_handler.queue_async_task(duration, std::forward<Fn>(fn));
		}

		template <class Fn>
		bool queue_async_task(Fn&& fn)
		{
			auto& task_handler = handlers::task_handler::get();
			return task_handler.queue_async_task(std::forward<Fn>(fn));
		}

	private:
		session();
		~session();

		friend class handlers::task_handler;

		void update();
		void update_object_manager();
		void update_console_commands();

	private:
		entt::registry registry_;
		entt::dispatcher dispatcher_;
	};
}
