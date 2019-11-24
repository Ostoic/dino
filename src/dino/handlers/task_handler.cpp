#include "task_handler.hpp"

#include "../wow/console.hpp"
#include "../wow/graphics.hpp"
#include "../settings.hpp"
#include "../session.hpp"
#include "../version.hpp"

#include <chrono>

namespace dino::handlers
{
	unsigned int task_handler::original_endscene = static_cast<unsigned int>
		(bind_value(wow::graphics::get_ptr_address()));

	void task_handler::install_hook()
	{
		auto& task_handler = task_handler::get();
		if (!task_handler.is_active())
			task_handler.hook();
	}

	void task_handler::uninstall_hook()
	{
		auto& task_handler = task_handler::get();
		if (task_handler.is_active())
			task_handler.unhook();
	}

	bool task_handler::is_active() const
	{
		return bind_value(wow::graphics::get_ptr_address()) != task_handler::original_endscene;
	}

	__declspec(naked) void endscene_hook()
	{
		using clock = std::chrono::high_resolution_clock;
		using namespace std::chrono_literals;

		static auto original_endscene = task_handler::original_endscene;

		// Save asm flags
		_asm
		{
			pushad
			pushfd
		}

		[] {
			static auto last_frame_time = clock::now();
			auto& task_handler = task_handler::get();

			const auto frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>
				(clock::now() - last_frame_time);

			if (frame_duration < settings::refresh_rate())
				return;

			last_frame_time = clock::now();

			auto& tasks = task_handler.tasks_;
			auto& services = task_handler.services_;
			task_handler.update_session();

			// Run services
			if (!services.empty())
				for (const auto& service : services)
					service.fn();

			// Run any new tasks
			if (!tasks.empty())
			{
				// This is synchronized since tasks are meant to run once, so it is more likely endscene
				// will race with another contending thread.
				auto lock = std::unique_lock<std::mutex>{task_handler.tasks_mutex_};
				if (lock.owns_lock())
				{
					while (!tasks.empty())
					{
						tasks.front()();
						tasks.pop();
					}
				}
			}
		}();

		// Restore any asm flags.
		_asm
		{
			popfd
			popad
			jmp original_endscene;
		};
	}

	void task_handler::update_session()
	{
		dino::session::get().update();
	}

	task_handler::task_handler()
	{
		task_handler::original_endscene = deref_as<unsigned int>(wow::graphics::get_ptr_address());
	}

	void task_handler::hook()
	{
		deref_as<fn_ptr<void()>>(wow::graphics::get_ptr_address())
			= endscene_hook;
	}

	void task_handler::unhook()
	{
		// Make task_handler unhook itself
		this->queue_task([] {
			deref_as<fn_ptr<void()>>(wow::graphics::get_ptr_address())
				= fn_ptr<void()>(static_cast<unsigned int>(task_handler::original_endscene));
		});
	}

	task_handler& task_handler::get()
	{
		static task_handler s_;
		return s_;
	}
}