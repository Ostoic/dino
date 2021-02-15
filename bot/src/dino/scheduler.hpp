#pragma once

#include <string>
#include <entt/entt.hpp>

#include "log.hpp"
#include "handlers/task_handler.hpp"

namespace dino
{
	class scheduler
	{
	public:

	public:
		// Queues a transient task to be run once the next time Event is emitted.
		template <class Event, class Fn>
		static bool queue_transient(Fn&& fn);

		template <class Fn>
		static bool queue_task(Fn&& fn);

		template <class Duration, class Fn>
		static bool queue_async_task(Duration duration, Fn&& fn);

		template <class Fn>
		static bool queue_async_task(Fn&& fn);

		static std::vector<std::string> get_event_list();

	public:
		template <class Event>
		static auto sink()
		{
			return get().dispatcher_.sink<Event>();
		}

		template <class Event>
		static void trigger()
		{
			get().dispatcher_.enqueue<Event>();
		}

		template <class Event>
		static void trigger(Event&& event)
		{
			get().dispatcher_.enqueue<Event>(std::forward<Event>(event));
		}

		template <class Event>
		static void update()
		{
			get().dispatcher_.update<Event>();
		}

		static void update()
		{
			get().dispatcher_.update();
		}

	private:
		template <class Event>
		static void handle_once(const Event& event);

		friend class session;

		static scheduler& get();

	private:
		entt::dispatcher dispatcher_;
	};
}

namespace dino
{
	template <class Event, class Fn>
	bool scheduler::queue_transient(Fn&& fn)
	{
		handlers::task_handler::get().transients<Event>()
			.emplace(std::forward<Fn>(fn));

		get().dispatcher_
			.sink<Event>()
			.connect<scheduler::handle_once<Event>>();

		return true;
	}

	template <class Fn>
	bool scheduler::queue_task(Fn&& fn)
	{
		return handlers::task_handler::queue_task(std::forward<Fn>(fn));
	}

	template <class Duration, class Fn>
	bool scheduler::queue_async_task(Duration duration, Fn&& fn)
	{
		return handlers::task_handler::queue_async_task(duration, std::forward<Fn>(fn));
	}

	template <class Fn>
	bool scheduler::queue_async_task(Fn&& fn)
	{
		log::info("scheduler::queue_async_task");
		return handlers::task_handler::queue_async_task(std::forward<Fn>(fn));
	}

	template <class Event>
	static void scheduler::handle_once(const Event& event)
	{
		std::queue<std::function<handlers::task_handler::transient_state(const Event&)>>& transients
			= handlers::task_handler::get().transients<Event>();

		auto copy = transients;
		while (!transients.empty())
			transients.pop();

		while (!copy.empty())
		{
			auto& fn = copy.front();
			const auto state = fn(event);
			if (state == handlers::task_handler::transient_state::pass)
				transients.push(fn);

			copy.pop();
		}

		get().dispatcher_
			.sink<Event>()
			.disconnect<scheduler::handle_once<Event>>();
	}
}