#include "session.hpp"
#include "settings.hpp"
#include "version.hpp"
#include "log.hpp"
#include "debug.hpp"

#include "emitters/gamestate_emitter.hpp"
#include "emitters/endscene_emitter.hpp"

#include "events/endscene_events.hpp"
#include "events/warden_events.hpp"
#include "events/dino_events.hpp"
#include "events/glue_events.hpp"
#include "hook/vmt_hook.hpp"

#include "wow/world/traceline.hpp"
#include "wow/glue/glue.hpp"
#include "wow/cvar.hpp"
#include "wow/lua.hpp"
#include "wow/net/connection.hpp"

#include <obfuscator.hpp>

namespace dino
{
	std::string session::identity()
	{
		const auto realmlist = wow::cvar::lookup("realmList");
		const auto accountName = std::string{&deref_as<const char>(wow::offsets::account::name)};

		if (!realmlist.valid() || accountName.empty())
			return {};

		return fmt::format("{}:{}", realmlist.value(), accountName);
	}

	void session::start()
	{
		try
		{
			spdlog::set_level(spdlog::level::debug);
			wow::console::enable();
			wow::console::open();

			// Setup task handler for .queue_task()
			scheduler::sink<events::endscene_frame>()
				.connect<handlers::task_handler::handle>();

			scheduler::queue_task([] {
				log::info(OBFUSCATE("{} loaded"), dino::version::format());
			});

			log::info("before queue_async_task");
			using namespace std::chrono_literals;
			scheduler::queue_task([] {
				log::info("hi");
				if (wow::glue::current_screen() == wow::glue::screen::login)
				{
					log::info("login screen!");
					const auto realmlist = wow::cvar::lookup("realmList");
					if (!realmlist.valid())
						return;

					if (realmlist.value() == "10.179.205.114")
						wow::lua::run(OBFUSCATE("DefaultServerLogin('admin', 'admin')"));
				}
			});

			debug::dev();

			emitters::endscene_emitter::install();
			emitters::gamestate_emitter::install();
			log::info(OBFUSCATE("done!"));
		}
		catch (const std::exception & e)
		{
			log::critical(OBFUSCATE("Exception: {}"), e.what());
		}
	}

	void session::exit()
	{
		scheduler::enqueue<events::dino_exit>();

		// Setup task handler for .queue_task()
		scheduler::sink<events::endscene_frame>()
			.disconnect<handlers::task_handler::handle>();

		emitters::gamestate_emitter::uninstall();
		emitters::endscene_emitter::uninstall();

		wow::console::close();
		wow::console::disable();
	}

	session& session::get()
	{
		static session s_;
		return s_;
	}

	entt::registry& session::registry() noexcept
	{
		return get().registry_;
	}

	scheduler& session::dispatcher() noexcept
	{
		return scheduler::get();
	}

	std::string session::status_message()
	{
		return "";
	}

}