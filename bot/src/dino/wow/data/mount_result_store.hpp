#pragma once

#include "store.hpp"
#include "../guid.hpp"

namespace dino::wow::data
{
	struct mount_result_store
	{
	public:
		explicit mount_result_store(address store_base);
		explicit mount_result_store(data::store&& store);
		explicit mount_result_store() = default;

		mount_result_store* operator->() noexcept;
		const mount_result_store* operator->() const noexcept;

	public:
		void set_flags(unsigned int flags);
		unsigned int flags() const;

		void seek_end();

	private:
		mutable data::store store_;
	};
}
