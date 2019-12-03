#include "chat.hpp"
#include "console.hpp"

namespace dino::wow::chat
{
	message parse_data_store(wow::data_store store)
	{
		return message{store};
	}

	message::message(data_store store)
		: store_{store}
		, msg_type_{static_cast<message::type>(store->pull<char>())}
		, language_{store->pull<int>()}
		, sender_{store->pull<guid>()}
	{
		store->pull<int>();
		if (static_cast<int>(msg_type_) == 8)
			return;

		if (msg_type_ == message::type::channel)
			//store_->pull<std::string>(128);
			return;

		receiver_ = store->pull<guid>();
		auto length = store_->pull<int>();
		char* data = store_->pull<char*>(length);
		text_ = std::string{data, static_cast<unsigned int>(length)};
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

		if (msg_type_ == message::type::channel)
			//store_->pull<std::string>(128);
			return "";

		store_->pull<guid>();
		auto length = store_->pull<int>();
		char* data = store_->pull<char*>(length);
		return std::string{data, static_cast<unsigned int>(length)};
	}

	std::string message::channel() const noexcept
	{
		store_->set_cursor(2 + sizeof(char) + sizeof(int) + sizeof(guid) + sizeof(int));
		if (static_cast<int>(msg_type_) == 8)
			return {};

		//if (msg_type_ == message::type::channel)
			//return store_->pull<std::string>(128);

		return {};
	}

	const std::string& message::chat_tag() const noexcept
	{
		return chat_tag_;
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
		return receiver_;
	}

	bool message::is_gm_chat() const noexcept
	{
		return false;
	}
}