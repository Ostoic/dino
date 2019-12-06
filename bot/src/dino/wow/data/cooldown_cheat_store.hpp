#pragma once

#include "store.hpp"
#include "../guid.hpp"

namespace dino::wow::data
{
	struct cooldown_cheat_store
	{
	public:
		explicit cooldown_cheat_store(address store_base);
		explicit cooldown_cheat_store(data::store store);

		cooldown_cheat_store* operator->() noexcept;
		const cooldown_cheat_store* operator->() const noexcept;

	public:
		void set_receiver(guid receiver);
		guid receiver() const;

		void seek_end();

	private:
		mutable data::store store_;
	};
}
