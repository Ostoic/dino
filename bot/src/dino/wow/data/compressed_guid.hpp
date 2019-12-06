#pragma once

#include <cstddef>

#include "../guid.hpp"
#include "../data/store.hpp"

namespace dino::wow::data
{
	class compressed_guid
	{
	public:
		explicit compressed_guid(data::store store);

		explicit operator std::uint64_t() const noexcept;
		explicit operator wow::guid() const noexcept;

	public:
		int low() const noexcept;
		int high() const noexcept;

	private:
		mutable data::store store_;
	};
}