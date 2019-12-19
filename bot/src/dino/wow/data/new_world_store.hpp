#pragma once

#include "../data/store.hpp"
#include "../guid.hpp"

#include <string_view>
#include <optional>

namespace dino::wow::data
{
	struct new_world_store
	{
	public:
		explicit new_world_store(address store_base);
		explicit new_world_store(data::store&& store);
		explicit new_world_store() = default;

		new_world_store* operator->() noexcept;
		const new_world_store* operator->() const noexcept;

	public:
		void set_map_index(unsigned int index);
		void set_x(float x);
		void set_y(float y);
		void set_z(float z);
		void set_rotation(float rotation);

		unsigned int map_index() const;
		float x() const;
		float y() const;
		float z() const;
		float rotation() const;

		void seek_end();

	private:
		mutable data::store store_;
	};
}
