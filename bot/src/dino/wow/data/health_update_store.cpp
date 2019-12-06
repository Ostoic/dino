#include "health_update_store.hpp"

namespace dino::wow::data
{
	health_update_store::health_update_store(address store_base)
		: health_update_store{data::store{store_base}}
	{}

	health_update_store::health_update_store(data::store store)
		: store_{store}
	{
		store_->restore_cursor();
	}

	health_update_store* health_update_store::operator->() noexcept
	{
		return this;
	}

	const health_update_store* health_update_store::operator->() const noexcept
	{
		return this;
	}

	void health_update_store::set_receiver(const guid receiver)
	{
		store_->put(receiver);
		store_->restore_cursor();
	}

	void health_update_store::set_amount_healed(const unsigned int amount)
	{
		store_->pull<guid>();
		store_->put(amount);
		store_->restore_cursor();
	}

	guid health_update_store::receiver() const
	{
		const auto result = store_->pull<guid>();
		store_->restore_cursor();
		return result;
	}

	unsigned int health_update_store::amount_healed() const
	{
		store_->pull<guid>();
		const auto result = store_->pull<unsigned int>();
		store_->restore_cursor();
		return result;
	}

	void health_update_store::seek_end()
	{
		store_->seek(sizeof(guid) + sizeof(unsigned int));
	}
}