#pragma once

#include "../data/store.hpp"
#include "../guid.hpp"

#include <string_view>

namespace dino::wow::data
{
	class text_emote_store
	{
	public:
		explicit text_emote_store(address cdata);
		explicit text_emote_store(data::store&& store);
		explicit text_emote_store() = default;

		text_emote_store* operator->() noexcept { return this; }
		const text_emote_store* operator->() const noexcept { return this; }

	public:
		guid sender_guid() const;

		std::string target_name() const;

	private:
		mutable data::store store_;
	};

}
