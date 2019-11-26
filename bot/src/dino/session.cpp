#include "session.hpp"

#include "wow/console.hpp"
#include "wow/graphics.hpp"
#include "version.hpp"

#include "handlers/task_handler.hpp"
#include "handlers/command_handler.hpp"
#include "events/console_events.hpp"

#include <unordered_set>

// headers for code-to-rewrite
#include "wow/net/messages.hpp"
#include "wow/data_store.hpp"
#include "debug.hpp"

namespace dino
{
	session& session::start()
	{
		static session singleton;
		return singleton;
	}

	session& session::get()
	{
		return session::start();
	}

	void session::update_console_commands()
	{
		static unsigned int last_line_executed = 0;
		if (wow::console::num_lines() != last_line_executed)
		{
			dispatcher_.enqueue(events::new_console_command{wow::console::last_command()});
			last_line_executed = wow::console::num_lines();
		}
	}

	void session::update()
	{
		this->update_console_commands();
		dispatcher_.update();
	}

	int smsg_chat_handler(int a1, int a2, int a3, void* cdata)
	{
		auto original_handler
			= bind_fn<int(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_messagechat_fn);

		return original_handler(a1, a2, a3, cdata);
	}

	int smsg_gm_chat_handler(int a1, int a2, int a3, void* cdata)
	{
		auto original_handler
			= bind_fn<int(int, int, int, void*)>(wow::offsets::net::messages::packet_smsg_gm_messagechat_fn);

		// Todo: Reimplement the important parts of the smsg chat handler

		// Todo: Revise the following RE method; this way assumes one path through the smsg chat handler,
		// so it's possible that 'bytes_pulled' is different when we get to pull the message,
		// based on the chat message type

		// 0. nothing						(bytes_pulled: 2)
		// 1. pull int8 -> message type		(after: bytes_pulled == 3)
		// 2. pull int32 -> language		(after: bytes_pulled == 7)
		// 3. pull int64 -> sender guid		(after: bytes_pulled == 15)
		// 4. pull int32 -> a9??			(after: bytes_pulled == 19)
		// 5. pull int32 -> max length		(after: bytes_pulled == 23)
		// 6. pull string count -> idkk		(after: bytes_pulled == 27)
		// 7. pull int64 -> target guid		(after: bytes_pulled == 35)

		auto data = wow::data_store{cdata};

		const auto original_cursor = data.cursor();
		const auto message_type = data.pull<char>();
		const auto language = data.pull<int>();
		const auto sender_guid = data.pull<std::int64_t>();
		const auto unk1 = data.pull<int>();

		// 17 -> channel message
		//if (message_type == 17)

		// Todo: Figure out what the different types of chat messages are
		wow::console::dino("[SMSG_GM_MESSAGECHAT] data size = {}, cursor pos = {}", data.size(), data.cursor());
		wow::console::dino("[SMSG_GM_MESSAGECHAT] language = {}, msg type = {}", language, message_type);
		data.set_cursor(original_cursor);

		return original_handler(a1, a2, a3, cdata);
	}

	session::session()
	{
		using namespace std::chrono_literals;

		wow::console::enable();
		wow::console::open();
		handlers::task_handler::install_hook();

		dispatcher_
			.sink<events::new_console_command>()
			.connect<handlers::command_handler::handle>();

		this->queue_task([]{
			wow::console::dino("{} loaded", dino::version::format());
		});

		//if (version::debug)
			dino::allocate_console();

		this->queue_task([] {
			auto set_message_handler
				= bind_fn<void(wow::net::messages::server, void*, wow::data_store*)>
					(wow::offsets::net::client_services::set_message_handler_fn);

			set_message_handler(
				wow::net::messages::server::chat_message,
				smsg_chat_handler,
				nullptr
			);

			set_message_handler(
				wow::net::messages::server::gm_chat_message,
				smsg_gm_chat_handler,
				nullptr
			);
		});
	}

	session::~session()
	{
		//handlers::task_handler::uninstall_hook();
	}

	entt::registry& session::registry() noexcept
	{
		return registry_;
	}

	entt::dispatcher& session::dispatcher() noexcept
	{
		return dispatcher_;
	}
}