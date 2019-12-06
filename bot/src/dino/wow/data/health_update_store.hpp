#pragma once

#include "store.hpp"
#include "../guid.hpp"

namespace dino::wow::data
{
	struct health_update_store
	{
	public:
		explicit health_update_store(address store_base);
		explicit health_update_store(data::store store);

		health_update_store* operator->() noexcept;
		const health_update_store* operator->() const noexcept;

	public:
		void set_receiver(guid receiver);
		void set_amount_healed(unsigned int amount);

		guid receiver() const;
		unsigned int amount_healed() const;

		void seek_end();

	private:
		mutable data::store store_;
	};
}
