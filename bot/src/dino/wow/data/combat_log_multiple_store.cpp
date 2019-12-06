#include "combat_log_multiple_store.hpp"

namespace dino::wow::data
{
	combat_log_multiple_store::combat_log_multiple_store(address store_base)
		: combat_log_multiple_store{data::store{store_base}}
	{}

	combat_log_multiple_store::combat_log_multiple_store(data::store store)
		: store_{store}
	{
		store_->restore_cursor();
	}

	combat_log_multiple_store* combat_log_multiple_store::operator->() noexcept
	{
		return this;
	}

	const combat_log_multiple_store* combat_log_multiple_store::operator->() const noexcept
	{
		return this;
	}

	void combat_log_multiple_store::set_count(const unsigned int count)
	{
		store_->put(count);
		store_->restore_cursor();
	}

	void combat_log_multiple_store::set_time(const unsigned int time)
	{
		store_->pull<unsigned int>();
		store_->put(time);
		store_->restore_cursor();
	}

	unsigned int combat_log_multiple_store::count() const
	{
		const auto result = store_->pull<unsigned int>();
		store_->restore_cursor();
		return result;
	}

	unsigned int combat_log_multiple_store::time() const
	{
		store_->pull<unsigned int>();
		const auto result = store_->pull<unsigned int>();
		store_->restore_cursor();
		return result;
	}
}