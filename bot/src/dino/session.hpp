#pragma once

#include <chrono>
#include <memory>
#include <vector>
#include <typeinfo>
#include <functional>
#include <concepts>
#include <entt/entt.hpp>
#include <spdlog/sinks/basic_file_sink.h>

#include "emitters/endscene_emitter.hpp"
#include "handlers/task_handler.hpp"
#include "wow/chat.hpp"
#include "offset.hpp"

namespace dino
{
	namespace handlers { class task_handler; }

	class session
	{
	public:
		static session& get();
		static void start();
		static void exit();

		using clock = std::chrono::high_resolution_clock;

	public:
		entt::registry& registry() noexcept;
		entt::dispatcher& dispatcher() noexcept;

		template <class Fn>
		bool queue_task(Fn&& fn);

		template <class Duration, class Fn>
		bool queue_async_task(Duration duration, Fn&& fn);

		template <class Fn>
		bool queue_async_task(Fn&& fn);

	private:
		template <class Event, auto Fn>
		bool add_service()
		{
			this->dispatcher()
				.sink<Event>()
				.connect<Fn>();

			return true;
		}

		template <class Event>
		void remove_service();

	private:
		friend class emitters::endscene_emitter;

		void update();
		void update_object_manager();
		void update_console_commands();

	private:
		entt::registry registry_;
		entt::dispatcher dispatcher_;
	};
}

namespace dino
{
	template <class Fn>
	bool session::queue_task(Fn&& fn)
	{
		return handlers::task_handler::queue_task(std::forward<Fn>(fn));
	}

	template <class Duration, class Fn>
	bool session::queue_async_task(Duration duration, Fn&& fn)
	{
		return handlers::task_handler::queue_async_task(duration, std::forward<Fn>(fn));
	}

	template <class Fn>
	bool session::queue_async_task(Fn&& fn)
	{
		return handlers::task_handler::queue_async_task(std::forward<Fn>(fn));
	}

	template <class Event>
	void session::remove_service()
	{
		//this->dispatcher().sink<Event>().
		//this->dispatcher()

		//emitters::endscene_emitter::get().remove_service(name);
	}
}
