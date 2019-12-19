#include "message.hpp"
#include "../console.hpp"
#include "../guid.hpp"
#include "../../log.hpp"
#include "../data/message_store.hpp"

namespace dino::wow::chat
{
	message::message(data::store&& store)
	{
		auto mstore = data::message_store{std::move(store)};
		text_ = mstore->text();
		channel_ = mstore->channel().value_or("");
		msg_type_ = mstore->msg_type();
		language_ = mstore->language();
		sender_ = mstore->sender();
		is_gm_chat_ = mstore->is_gm_chat();
	}

	const std::string& message::text() const noexcept
	{
		return text_;
	}

	const std::string& message::channel() const noexcept
	{
		return channel_;
	}

	message::type message::msg_type() const noexcept
	{
		return msg_type_;
	}

	int message::language() const noexcept
	{
		return language_;
	}

	guid message::sender() const noexcept
	{
		return sender_;
	}

	bool message::is_gm_chat() const noexcept
	{
		return is_gm_chat_;
	}

	void add_message(const message& message)
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
			message.text().c_str(),
			message.msg_type(),
			nullptr,
			message.language(),
			message.channel().c_str(),
			nullptr,
			nullptr,
			message.sender(),
			0,
			guid{},
			0,
			message.is_gm_chat(),
			0
		);

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

	std::string to_string(const message::type type)
	{
		const auto sv = to_string_view(type);
		return std::string{sv.data(), sv.size()};
	}
}