#include "mount_result_store.hpp"

namespace dino::wow::data
{
	mount_result_store::mount_result_store(address store_base)
		: store_{store_base}
	{}

	mount_result_store::mount_result_store(data::store&& store)
		: store_{std::move(store)}
	{
		store_->restore_cursor();
	}

	mount_result_store* mount_result_store::operator->() noexcept
	{
		return this;
	}

	const mount_result_store* mount_result_store::operator->() const noexcept
	{
		return this;
	}

	void mount_result_store::set_flags(const unsigned int flags)
	{
		store_->put(flags);
		store_->restore_cursor();
	}

	unsigned int mount_result_store::flags() const
	{
		const auto result = store_->pull<unsigned int>();
		store_->restore_cursor();
		return result;
	}

	void mount_result_store::seek_end()
	{
		store_->seek(sizeof(unsigned int));
	}
}