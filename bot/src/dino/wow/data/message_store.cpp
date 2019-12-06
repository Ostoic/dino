#include "message_store.hpp"
#include "../console.hpp"
#include "../guid.hpp"
#include "../../log.hpp"

namespace dino::wow::data
{
	message_store::message_store(data::store store, const bool is_gm_chat)
		: store_{store}
		, is_gm_chat_{is_gm_chat}
		, msg_type_{static_cast<chat::message::type>(store->pull<char>())}
	{
		store->restore_cursor();
	}

	message_store* message_store::operator->()
	{
		return this;
	}

	const message_store* message_store::operator->() const
	{
		return this;
	}

	void message_store::set_type(const chat::message::type type)
	{
		store_->put<char>(static_cast<char>(type));
		store_->restore_cursor();
	}

	void message_store::set_language(const int language)
	{
		store_->set_cursor(2 + sizeof(char));
		store_->put<int>(language);
		store_->restore_cursor();
	}

	void message_store::set_sender(const guid sender)
	{
		store_->set_cursor(2 + sizeof(char) + sizeof(int));
		store_->put<guid>(sender);
		store_->restore_cursor();
	}

	std::string message_store::text() const noexcept
	{
		log::debug("[message_store::text] type: {}", to_string_view(msg_type_));
		store_->set_cursor(2 + sizeof(char) + sizeof(int) + sizeof(guid) + sizeof(int));
		if (static_cast<int>(msg_type_) == 8)
			return {};

		if (msg_type_ == chat::message::type::monster_say		||
			msg_type_ == chat::message::type::monster_party		||
			msg_type_ == chat::message::type::monster_yell		||
			msg_type_ == chat::message::type::monster_whisper	||
			msg_type_ == chat::message::type::monster_emote		||
			msg_type_ == chat::message::type::raid_boss_emote	||
			msg_type_ == chat::message::type::raid_boss_whisper)
		{
			const auto sender_name = std::string{store_->pull<char*>(store_->pull<int>())};
			log::debug("[message_store::text] sender_name: {}", sender_name);
			const auto receiver = store_->pull<guid>();
			log::debug("[message_store::text] receiver: {}", receiver);

			return std::string{store_->pull<char*>(store_->pull<int>())};
		}
		else
		{
			if (is_gm_chat_)
			{
				auto length = store_->pull<int>();
				log::debug("[message_store::text] is_gm_chat_: {}", is_gm_chat_);
				store_->pull<char*>(length);
			}

			if (msg_type_ == chat::message::type::channel)
				log::debug("[message_store::text] channel: {}", store_->pull<std::string>(128));

			store_->pull<guid>();
			auto length = store_->pull<int>();
			char* data = store_->pull<char*>(length);
			return std::string{data};
		}
	}

	std::optional<std::string> message_store::channel() const noexcept
	{
		log::debug("[message_store::channel] type: {}", to_string_view(msg_type_));
		store_->set_cursor(2 + sizeof(char) + sizeof(int) + sizeof(guid) + sizeof(int));
		if (static_cast<int>(msg_type_) == 8)
			return {};

		if (msg_type_ == chat::message::type::monster_say		||
			msg_type_ == chat::message::type::monster_party		||
			msg_type_ == chat::message::type::monster_yell		||
			msg_type_ == chat::message::type::monster_whisper	||
			msg_type_ == chat::message::type::monster_emote		||
			msg_type_ == chat::message::type::raid_boss_emote	||
			msg_type_ == chat::message::type::raid_boss_whisper)
			return {};
		else
		{
			log::debug("[message_store::channel] is_gm_chat_: {}", is_gm_chat_);
			if (is_gm_chat_)
				store_->pull<char*>(store_->pull<int>());

			if (msg_type_ == chat::message::type::channel)
				return store_->pull<std::string>(128);
		}

		return {};
	}

	chat::message::type message_store::msg_type() const noexcept
	{
		auto result = chat::message::type{store_->pull<char>()};
		store_->restore_cursor();
		return result;
	}

	int message_store::language() const noexcept
	{
		store_->set_cursor(2 + sizeof(char));
		auto result = store_->pull<int>();
		store_->restore_cursor();
		return result;
	}

	guid message_store::sender() const noexcept
	{
		store_->set_cursor(2 + sizeof(char) + sizeof(int));
		auto result = store_->pull<guid>();
		store_->restore_cursor();
		return result;
	}

	bool message_store::is_gm_chat() const noexcept
	{
		return false;
	}
}