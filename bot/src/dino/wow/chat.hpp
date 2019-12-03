#pragma once

#include "data_store.hpp"
#include "guid.hpp"

namespace dino::wow::chat
{
	class message
	{
	public:
		enum class type : char
		{
			say = 1,
			yell = 6,
			channel = 17,
		};

	public:
		explicit message(data_store store);

		message* operator->()
		{
			return this;
		}

		const message* operator->() const
		{
			return this;
		}

	public:
		void set_type(type type);
		void set_language(int language);
		void set_sender(guid sender);

		std::string text() const noexcept;
		std::string channel() const noexcept;
		const std::string& chat_tag() const noexcept;
		type msg_type() const noexcept;
		int language() const noexcept;
		guid sender() const noexcept;
		guid receiver() const noexcept;
		bool is_gm_chat() const noexcept;

	private:
		mutable data_store store_;
		std::string text_;
		std::string channel_;
		std::string chat_tag_;
		type msg_type_;
		int language_;
		guid sender_;
		guid receiver_;
		bool is_gm_chat_;
	};

	message parse_data_store(wow::data_store store);
}