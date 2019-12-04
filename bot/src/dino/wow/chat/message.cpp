#include "message.hpp"
#include "../console.hpp"
#include "../guid.hpp"

namespace dino::wow::chat
{
	message::message(data_store store, const bool is_gm_chat)
		: store_{store}
		, is_gm_chat_{is_gm_chat}
		, msg_type_{static_cast<message::type>(store->pull<char>())}
	{
		store->restore_cursor();
	}

	void message::set_type(const type type)
	{
		store_->put<char>(static_cast<char>(type));
		store_->restore_cursor();
	}

	void message::set_language(const int language)
	{
		store_->set_cursor(2 + sizeof(char));
		store_->put<int>(language);
		store_->restore_cursor();
	}

	void message::set_sender(const guid sender)
	{
		store_->set_cursor(2 + sizeof(char) + sizeof(int));
		store_->put<guid>(sender);
		store_->restore_cursor();
	}

	std::string message::text() const noexcept
	{
		store_->set_cursor(2 + sizeof(char) + sizeof(int) + sizeof(guid) + sizeof(int));
		if (static_cast<int>(msg_type_) == 8)
			return {};

		if (is_gm_chat_)
		{
			auto length = store_->pull<int>();
			store_->pull<char*>(length);
		}

		if (msg_type_ == message::type::channel)
			store_->pull<std::string>(128);
			//return "";

		store_->pull<guid>();
		auto length = store_->pull<int>();
		char* data = store_->pull<char*>(length);
		return std::string{data};
	}

	std::string message::channel() const noexcept
	{
		store_->set_cursor(2 + sizeof(char) + sizeof(int) + sizeof(guid) + sizeof(int));
		if (static_cast<int>(msg_type_) == 8)
			return {};

		if (is_gm_chat_)
		{
			auto length = store_->pull<int>();
			store_->pull<char*>(length);
		}

		if (msg_type_ == message::type::channel)
			return store_->pull<std::string>(128);

		return {};
	}

	message::type message::msg_type() const noexcept
	{
		auto result = message::type{store_->pull<char>()};
		store_->restore_cursor();
		return result;
	}

	int message::language() const noexcept
	{
		store_->set_cursor(2 + sizeof(char));
		auto result = store_->pull<int>();
		store_->restore_cursor();
		return result;
	}

	guid message::sender() const noexcept
	{
		store_->set_cursor(2 + sizeof(char) + sizeof(int));
		auto result = store_->pull<guid>();
		store_->restore_cursor();
		return result;
	}

	guid message::receiver() const noexcept
	{
		return {};
	}

	bool message::is_gm_chat() const noexcept
	{
		return false;
	}

	void add_message(const std::string& message)
	{
		auto add_chat_message_fn
			= bind_fn<void(
				const char*,
				message::type,
				const char*,
				int,
				const char*,
				const char*,
				const char*,
				guid,
				int,
				guid,
				int,
				char,
				int
			)>(offsets::chat::add_chat_message_fn);

		add_chat_message_fn(
			message.c_str(),
			message::type::system,
			nullptr,
			0,
			nullptr,
			nullptr,
			nullptr,
			guid{},
			0,
			guid{},
			0,
			0,
			0
		);
	}

}