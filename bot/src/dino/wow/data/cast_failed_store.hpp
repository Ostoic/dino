#pragma once

#include "store.hpp"

namespace dino::wow::data
{
	struct cast_failed_store
	{
	public:
		explicit cast_failed_store(address store_base);
		explicit cast_failed_store(data::store store);

		cast_failed_store* operator->() noexcept;
		const cast_failed_store* operator->() const noexcept;

	public:
		void set_pending_spell_cast(unsigned char value);
		void set_spell_id(unsigned int id);
		void set_error(unsigned char value);

		unsigned char pending_spell_cast() const;
		unsigned int spell_id() const;
		unsigned char error() const;

		void seek_end();

	private:
		mutable data::store store_;
	};
}
