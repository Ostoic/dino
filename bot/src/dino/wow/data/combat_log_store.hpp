#pragma once

#include "store.hpp"

namespace dino::wow::data
{
	struct combat_log_store
	{
	public:
		explicit combat_log_store(address store_base);
		explicit combat_log_store(data::store&& store);
		explicit combat_log_store() = default;

		combat_log_store* operator->() noexcept;
		const combat_log_store* operator->() const noexcept;

	public:
		void set_count(unsigned int count);
		void set_tick_count(unsigned int count);

		unsigned int count() const;
		unsigned int tick_count() const;

		void seek_end();

	private:
		mutable data::store store_;
	};
}
