#include "combat_log_store.hpp"

namespace dino::wow::data
{
	combat_log_store::combat_log_store(address store_base)
		: store_{store_base}
	{}

	combat_log_store::combat_log_store(data::store&&store)
		: store_{std::move(store)}
	{
		store_->restore_cursor();
	}

	combat_log_store* combat_log_store::operator->() noexcept
	{
		return this;
	}

	const combat_log_store* combat_log_store::operator->() const noexcept
	{
		return this;
	}

	void combat_log_store::set_count(const unsigned int count)
	{
		store_->put(count);
		store_->restore_cursor();
	}

	void combat_log_store::set_tick_count(const unsigned int count)
	{
		store_->put(count);
		store_->restore_cursor();
	}

	unsigned int combat_log_store::count() const
	{
		const auto result = store_->pull<unsigned int>();
		store_->restore_cursor();
		return result;
	}

	unsigned int combat_log_store::tick_count() const
	{
		store_->pull<unsigned int>();
		const auto result = store_->pull<unsigned int>();
		store_->restore_cursor();
		return result;
	}
}