#include "emote.hpp"
#include "../console.hpp"
#include "../guid.hpp"

namespace dino::wow::chat
{
	emote::emote(const address cdata)
		: emote{data::store{cdata}}
	{}

	emote::emote(const data::store store)
		: store_{store}
	{}

	guid emote::sender_guid() const
	{
		const auto result = store_->pull<wow::guid>();
		store_->restore_cursor();
		return guid{result};
	}

	std::string emote::target_name() const
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