#include "session.hpp"

#include "settings.hpp"
#include "version.hpp"

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
#include "log.hpp"
#include "debug.hpp"

#include <obfuscator.hpp>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
			//if (dino::version::debug)
			spdlog::set_level(spdlog::level::debug);

			settings::initialize();
			wow::console::enable();
			wow::console::open();

			// Setup task handler for .queue_task()
			dispatcher::sink<events::endscene_frame>()
				.connect<handlers::task_handler::handle>();

			dispatcher::queue_task([] {
				log::info(OBFUSCATE("{} loaded"), dino::version::format());
			});

			log::info("before queue_async_task");
			using namespace std::chrono_literals;
			dispatcher::queue_task([] {
				log::info("hi");
				if (wow::glue::current_screen() == wow::glue::screen::login)
				{
					log::info("login screen!");
					const auto realmlist = wow::cvar::lookup("realmList");
					if (!realmlist.valid())
						return;

					if (realmlist.value() == "logon.warmane.com")
					{
						wow::lua::run(
							OBFUSCATE("DefaultServerLogin('{}', '{}')"),
							OBFUSCATE("Jewishpig"),
							OBFUSCATE("Gb2gMyBNrSDvijtb")
						);
					}

					else if (realmlist.value() == "danktown.ddns.net")
					{
						wow::lua::run(
							OBFUSCATE("DefaultServerLogin('{}', '{}')"),
							OBFUSCATE("admin"),
							OBFUSCATE("sexton12")
						);
					}
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
		dispatcher::enqueue<events::dino_exit>();

		// Setup task handler for .queue_task()
		dispatcher::sink<events::endscene_frame>()
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

	dispatcher& session::dispatcher() noexcept
	{
		return dispatcher::get();
	}

	std::string session::status_message()
	{
		return "";
	}

}