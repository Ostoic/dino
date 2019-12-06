#pragma once

#include "../data/store.hpp"
#include "../guid.hpp"
#include "../chat/message.hpp"

#include <string_view>
#include <optional>

namespace dino::wow::data
{
	struct message_store
	{
	public:
		explicit message_store(data::store store, bool is_gm_chat = false);

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

	private:
		mutable data::store store_;
		chat::message::type msg_type_;
		bool is_gm_chat_;
	};
}
