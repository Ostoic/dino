#pragma once

#include "../data_store.hpp"
#include "../guid.hpp"

#include <string_view>

namespace dino::wow::chat
{
	class emote
	{
	public:
		emote(data_store store);

		emote* operator->() noexcept { return this; }
		const emote* operator->() const noexcept { return this; }

	public:
		guid sender_guid() const;

		std::string target_name() const;

	private:
		mutable data_store store_;
	};

}
