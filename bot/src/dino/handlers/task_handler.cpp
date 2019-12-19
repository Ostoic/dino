#include "task_handler.hpp"

#include "../wow/console.hpp"
#include "../wow/graphics.hpp"
#include "../settings.hpp"
#include "../session.hpp"
#include "../version.hpp"

#include <chrono>

namespace dino::handlers
{
	task_handler& task_handler::get() noexcept
	{
		static task_handler s_;
		return s_;
	}

	void task_handler::handle(const events::endscene_frame& event)
	{
		using namespace std::chrono_literals;
		auto& handler = task_handler::get();

		//auto lock = std::unique_lock{handler.mutex_};
		//if (!lock.try_lock_for(100ms))
		//	return;

		while (!handler.tasks_.empty())
		{
			log::info("[task_handler::handler] task...");
			handler.tasks_.front()();
			handler.tasks_.pop();
		}
	}
}