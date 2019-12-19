#include "text_emote_store.hpp"
#include "../console.hpp"
#include "../guid.hpp"

namespace dino::wow::data
{
	text_emote_store::text_emote_store(const address store_base)
		: store_{store_base}
	{}

	text_emote_store::text_emote_store(data::store&& store)
		: store_{std::move(store)}
	{}

	guid text_emote_store::sender_guid() const
	{
		const auto result = store_->pull<wow::guid>();
		store_->restore_cursor();
		return guid{result};
	}

	std::string text_emote_store::target_name() const
	{
		store_->pull<wow::guid>();
		store_->pull<int>();
		store_->pull<int>();
		std::size_t max_length = store_->pull<int>();
		char* ptr = store_->pull<char*>(max_length);
		store_->restore_cursor();

		return std::string{ptr, max_length};
	}
}