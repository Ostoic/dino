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
#include "wow/data/message_store.hpp"
#include "offset.hpp"

namespace dino
{
	namespace handlers { class task_handler; }

	enum class status
	{
		idle,
	};

	class session
	{
	public:
		static void start();
		static void exit();

		using clock = std::chrono::high_resolution_clock;

	public:
		static entt::registry& registry() noexcept;
		static entt::dispatcher& dispatcher() noexcept;

		static std::string status_message();

		template <class Event, class Fn>
		static bool queue_task_on(Fn&& fn);

		template <class Fn>
		static bool queue_task(Fn&& fn);

		template <class Duration, class Fn>
		static bool queue_async_task(Duration duration, Fn&& fn);

		template <class Fn>
		static bool queue_async_task(Fn&& fn);

		template <class... Args>
		static bool run_script(Args&&... args);

	private:
		friend class emitters::endscene_emitter;

		static session& get();
		void update();

		static void install_loggers();
		static void uninstall_loggers();

	private:
		entt::registry registry_;
		entt::dispatcher dispatcher_;
	};
}

namespace dino
{
	//template <class Event, class Fn>
	//bool session::queue_task_on(Fn&& fn)
	//{
	//	auto& dispatcher = session::get().dispatcher();
	//	dispatcher
	//		.sink<Event>()
	//		.connect<
	//}

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

	template <class... Args>
	bool session::run_script(Args&&... args)
	{
		wow::lua::run(std::forward<Args>(args)...);
	}
}
