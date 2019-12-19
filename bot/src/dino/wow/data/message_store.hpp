#pragma once

#include "../data/store.hpp"
#include "../guid.hpp"
#include "../chat/message.hpp"

#include <string_view>
#include <optional>

namespace dino::wow::data
{
	template <bool IsGmChat = false>
	struct message_store
	{
	public:
		explicit message_store(data::store&& data);
		explicit message_store(address cdata);
		explicit message_store() = default;

		message_store* operator->();
		const message_store* operator->() const;

	public:
		void set_type(chat::message::type type);
		void set_language(int language);
		void set_sender(guid sender);

		std::string text() const noexcept;
		std::optional<std::string> channel() const noexcept;

		chat::message::type msg_type() const noexcept;
		int language() const noexcept;
		guid sender() const noexcept;
		bool is_gm_chat() const noexcept;

		void seek_end();

		unsigned int cursor() const;

		void restore_cursor() noexcept;

	private:
		mutable data::store store_;
		chat::message::type msg_type_;
	};
}

namespace dino::wow::data
{
	template <bool IsGmChat>
	message_store<IsGmChat>::message_store(data::store&& store)
		: store_{std::move(store)}
		, msg_type_{static_cast<chat::message::type>(store_->pull<char>())}
	{
		store_->restore_cursor();
	}

	template <bool IsGmChat>
	message_store<IsGmChat>::message_store(const address cdata)
		: message_store{data::store{cdata}}
	{}

	template <bool IsGmChat>
	message_store<IsGmChat>* message_store<IsGmChat>::operator->()
	{
		return this;
	}

	template <bool IsGmChat>
	const message_store<IsGmChat>* message_store<IsGmChat>::operator->() const
	{
		return this;
	}

	template <bool IsGmChat>
	void message_store<IsGmChat>::set_type(const chat::message::type type)
	{
		store_->restore_cursor();
		store_->put<char>(static_cast<char>(type));
		store_->restore_cursor();
	}

	template <bool IsGmChat>
	void message_store<IsGmChat>::set_language(const int language)
	{
		store_->seek(2 + sizeof(char));
		store_->put<int>(language);
		store_->restore_cursor();
	}

	template <bool IsGmChat>
	void message_store<IsGmChat>::set_sender(const guid sender)
	{
		store_->seek(2 + sizeof(char) + sizeof(int));
		store_->put<std::uint64_t>(static_cast<std::uint64_t>(sender));
		store_->restore_cursor();
	}

	template <bool IsGmChat>
	std::string message_store<IsGmChat>::text() const noexcept
	{
		store_->restore_cursor();
		const auto initial_cursor = store_->cursor();
		log::debug("[message_store::text] type: {}", to_string_view(this->msg_type()));
		log::debug("[message_store::text] type: {}", static_cast<unsigned int>(this->msg_type()));
		store_->seek(initial_cursor + sizeof(char) + sizeof(int) + sizeof(std::uint64_t) + sizeof(int));
		if (msg_type_ == chat::message::type::whisper_foreign)
		{
			store_->restore_cursor();
			return {};
		}

		if (msg_type_ == chat::message::type::monster_say ||
			msg_type_ == chat::message::type::monster_party ||
			msg_type_ == chat::message::type::monster_yell ||
			msg_type_ == chat::message::type::monster_whisper ||
			msg_type_ == chat::message::type::monster_emote ||
			msg_type_ == chat::message::type::raid_boss_emote ||
			msg_type_ == chat::message::type::raid_boss_whisper)
		{
			const auto max_length1 = store_->pull<unsigned int>();
			const auto sender_name = std::string{store_->pull<char*>(max_length1)};
			log::debug("[message_store::text] sender_name: {}", sender_name);
			const auto receiver = store_->pull<wow::guid>();
			log::debug("[message_store::text] receiver: {}", receiver);

			const auto max_length = store_->pull<unsigned int>();
			const auto result = std::string{store_->pull<char*>(max_length)};
			store_->restore_cursor();
			return result;
		}
		else
		{
			if (this->is_gm_chat())
			{
				auto length = store_->pull<int>();
				log::debug("[message_store::text] is_gm_chat_: {}", this->is_gm_chat());
				store_->pull<char*>(length);
			}

			if (msg_type_ == chat::message::type::channel)
				log::debug("[message_store::text] channel: {}", store_->pull<std::string>(128));

			store_->pull<guid>();
			auto length = store_->pull<int>();
			const char* data = store_->pull<const char*>(length);
			const auto result = std::string{data};
			store_->restore_cursor();
			return result;
		}
	}

	template <bool IsGmChat>
	std::optional<std::string> message_store<IsGmChat>::channel() const noexcept
	{
		store_->restore_cursor();
		const auto initial_cursor = store_->cursor();
		log::debug("[message_store::channel] type: {}", to_string_view(msg_type_));
		store_->seek(initial_cursor + sizeof(char) + sizeof(int) + sizeof(std::uint64_t) + sizeof(int));
		if (static_cast<int>(msg_type_) == 8)
			return {};

		if (msg_type_ == chat::message::type::monster_say ||
			msg_type_ == chat::message::type::monster_party ||
			msg_type_ == chat::message::type::monster_yell ||
			msg_type_ == chat::message::type::monster_whisper ||
			msg_type_ == chat::message::type::monster_emote ||
			msg_type_ == chat::message::type::raid_boss_emote ||
			msg_type_ == chat::message::type::raid_boss_whisper)
			return {};
		else
		{
			log::debug("[message_store::channel] is_gm_chat_: {}", this->is_gm_chat());
			if (this->is_gm_chat())
			{
				const auto max_length = store_->pull<int>();
				store_->pull<char*>(max_length);
			}

			if (msg_type_ == chat::message::type::channel)
			{
				const auto result = store_->pull<std::string>(128);
				store_->restore_cursor();
				return result;
			}
		}

		store_->restore_cursor();
		return {};
	}

	template <bool IsGmChat>
	chat::message::type message_store<IsGmChat>::msg_type() const noexcept
	{
		store_->restore_cursor();
		auto result = chat::message::type{store_->pull<char>()};
		store_->restore_cursor();
		return result;
	}

	template <bool IsGmChat>
	int message_store<IsGmChat>::language() const noexcept
	{
		store_->restore_cursor();
		const auto initial_cursor = store_->cursor();
		store_->seek(initial_cursor + sizeof(char));
		auto result = store_->pull<int>();
		store_->restore_cursor();
		return result;
	}

	template <bool IsGmChat>
	guid message_store<IsGmChat>::sender() const noexcept
	{
		store_->restore_cursor();
		const auto initial_cursor = store_->cursor();
		store_->seek(initial_cursor + sizeof(char) + sizeof(int));
		auto result = store_->pull<wow::guid>();
		store_->restore_cursor();
		return guid{result};
	}

	template <bool IsGmChat>
	bool message_store<IsGmChat>::is_gm_chat() const noexcept
	{
		return IsGmChat;
	}

	template <bool IsGmChat>
	void message_store<IsGmChat>::seek_end()
	{
		store_->restore_cursor();
		const auto initial_cursor = store_->cursor();
		log::debug("[message_store::seek_end] type: {}", to_string_view(msg_type_));
		store_->seek(initial_cursor + sizeof(char) + sizeof(int) + sizeof(std::uint64_t) + sizeof(int));
		if (static_cast<int>(msg_type_) == 8)
			return;

		if (msg_type_ == chat::message::type::monster_say ||
			msg_type_ == chat::message::type::monster_party ||
			msg_type_ == chat::message::type::monster_yell ||
			msg_type_ == chat::message::type::monster_whisper ||
			msg_type_ == chat::message::type::monster_emote ||
			msg_type_ == chat::message::type::raid_boss_emote ||
			msg_type_ == chat::message::type::raid_boss_whisper)
		{
			const auto max_length = store_->pull<unsigned int>();
			store_->pull<char*>(max_length);
			const auto sender_name = std::string{};
			log::debug("[message_store::seek_end] sender_name: {}", sender_name);
			const auto receiver = store_->pull<wow::guid>();
			log::debug("[message_store::seek_end] receiver: {}", receiver);

			store_->pull<char*>(store_->pull<int>());
		}
		else
		{
			if (this->is_gm_chat())
			{
				auto length = store_->pull<int>();
				log::debug("[message_store::seek_end] is_gm_chat_: {}", this->is_gm_chat());
				store_->pull<char*>(length);
			}

			if (msg_type_ == chat::message::type::channel)
				log::debug("[message_store::seek_end] channel: {}", store_->pull<std::string>(128));

			store_->pull<wow::guid>();
			auto length = store_->pull<int>();
			char* data = store_->pull<char*>(length);
		}
	}

	template <bool IsGmChat>
	unsigned int message_store<IsGmChat>::cursor() const
	{
		return store_->cursor();
	}

	template <bool IsGmChat>
	void message_store<IsGmChat>::restore_cursor() noexcept
	{
		store_->restore_cursor();
	}

}
