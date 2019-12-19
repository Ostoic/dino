#pragma once

#include <cstddef>

#include "../guid.hpp"
#include "../data/store.hpp"

namespace dino::wow::data
{
	class packed_guid
	{
	public:
		explicit packed_guid(wow::guid&& store);

		explicit operator std::uint64_t() const noexcept;
		explicit operator wow::guid() const noexcept;

	public:
		int low() const noexcept;
		int high() const noexcept;

		wow::guid unpack() const noexcept;

	private:
		wow::guid guid_;
	};
}