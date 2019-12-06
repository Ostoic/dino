#include "new_world_store.hpp"

namespace dino::wow::data
{
	new_world_store::new_world_store(address store_base)
		: new_world_store{data::store{store_base}}
	{}

	new_world_store::new_world_store(data::store store)
		: store_{store}
	{
		store_->restore_cursor();
	}

	new_world_store* new_world_store::operator->() noexcept
	{
		return this;
	}

	const new_world_store* new_world_store::operator->() const noexcept
	{
		return this;
	}

	void new_world_store::set_map_index(const unsigned int index)
	{
		store_->put(index);
		store_->restore_cursor();
	}

	void new_world_store::set_x(const float x)
	{
		store_->pull<unsigned int>();
		store_->put(x);
		store_->restore_cursor();
	}

	void new_world_store::set_y(const float y)
	{
		store_->pull<unsigned int>();
		store_->pull<float>();
		store_->put(y);
		store_->restore_cursor();
	}

	void new_world_store::set_z(const float z)
	{
		store_->pull<unsigned int>();
		store_->pull<float>();
		store_->pull<float>();
		store_->put(z);
		store_->restore_cursor();
	}

	void new_world_store::set_rotation(const float rotation)
	{
		store_->pull<unsigned int>();
		store_->pull<float>();
		store_->pull<float>();
		store_->pull<float>();
		store_->put(rotation);
		store_->restore_cursor();
	}

	unsigned int new_world_store::map_index() const
	{
		const auto result = store_->pull<unsigned int>();
		store_->restore_cursor();
		return result;
	}

	float new_world_store::x() const
	{
		store_->pull<unsigned int>();
		const auto result = store_->pull<float>();
		store_->restore_cursor();
		return result;
	}

	float new_world_store::y() const
	{
		store_->pull<unsigned int>();
		store_->pull<float>();
		const auto result = store_->pull<float>();
		store_->restore_cursor();
		return result;
	}

	float new_world_store::z() const
	{
		store_->pull<unsigned int>();
		store_->pull<float>();
		store_->pull<float>();
		const auto result = store_->pull<float>();
		store_->restore_cursor();
		return result;
	}

	float new_world_store::rotation() const
	{
		store_->pull<unsigned int>();
		store_->pull<float>();
		store_->pull<float>();
		store_->pull<float>();
		const auto result = store_->pull<float>();
		store_->restore_cursor();
		return result;
	}

	void new_world_store::seek_end()
	{
		store_->seek(sizeof(unsigned int) + 4 * sizeof(float));
	}

}