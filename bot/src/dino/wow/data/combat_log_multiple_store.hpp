#pragma once

#include "store.hpp"

namespace dino::wow::data
{
	struct combat_log_multiple_store
	{
	public:
		explicit combat_log_multiple_store(address store_base);
		explicit combat_log_multiple_store(data::store store);

		combat_log_multiple_store* operator->() noexcept;
		const combat_log_multiple_store* operator->() const noexcept;

	public:
		void set_count(unsigned int count);
		void set_time(unsigned int time);

		unsigned int count() const;
		unsigned int time() const;

		template <unsigned int PacketIndex>
		unsigned int packet()
		{
			store_->pull<unsigned int>(); // count
			store_->pull<unsigned int>(); // outer time


		}

		template <unsigned int PacketIndex>
		unsigned int opcode_of()
		{
			store_->pull<unsigned int>(); // count
			store_->pull<unsigned int>(); // outer time
		}

		void seek_end();

	private:
		mutable data::store store_;
	};
}
