#include "cast_failed_store.hpp"
#include "../console.hpp"
#include "../guid.hpp"
#include "../../log.hpp"

namespace dino::wow::data
{
	cast_failed_store::cast_failed_store(address store_base)
		: cast_failed_store{data::store{store_base}}
	{}

	cast_failed_store::cast_failed_store(data::store store)
		: store_{store}
	{
		store_->restore_cursor();
	}

	cast_failed_store* cast_failed_store::operator->() noexcept
	{
		return this;
	}

	const cast_failed_store* cast_failed_store::operator->() const noexcept
	{
		return this;
	}

	void cast_failed_store::set_pending_spell_cast(const unsigned char value)
	{
		store_->put(value);
		store_->restore_cursor();
	}

	void cast_failed_store::set_spell_id(const unsigned int id)
	{
		store_->pull<unsigned char>();
		store_->put(id);
		store_->restore_cursor();
	}

	void cast_failed_store::set_error(const unsigned char value)
	{
		store_->pull<unsigned char>();
		store_->pull<unsigned int>();
		store_->put(value);
		store_->restore_cursor();
	}

	unsigned char cast_failed_store::pending_spell_cast() const
	{
		const auto result = store_->pull<unsigned char>();
		store_->restore_cursor();
		return result;
	}

	unsigned int cast_failed_store::spell_id() const
	{
		store_->pull<unsigned char>();
		const auto result = store_->pull<unsigned int>();
		store_->restore_cursor();
		return result;
	}

	unsigned char cast_failed_store::error() const
	{
		store_->pull<unsigned char>();
		store_->pull<unsigned int>();
		const auto result = store_->pull<unsigned char>();
		store_->restore_cursor();
		return result;
	}
}