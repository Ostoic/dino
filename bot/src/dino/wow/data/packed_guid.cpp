#include "packed_guid.hpp"

#include "../offsets.hpp"
#include "../console.hpp"

namespace dino::wow::data
{
	namespace
	{
		wow::guid extract(data::store&& store)
		{
			const auto mask = store->pull<std::uint8_t>();

			if (mask == 0)
				return wow::guid{0};

			std::uint64_t res = 0;

			for (int i = 0; i < 8; i++)
				if ((mask & 1 << i) != 0)
					res += static_cast<std::uint64_t>(store->pull<std::uint8_t>()) << (i * 8);

			return wow::guid{res};
		}
	}

	packed_guid::packed_guid(wow::guid&& guid)
		: guid_{std::move(guid)}
	{}

	int packed_guid::low() const noexcept
	{
		return static_cast<int>(static_cast<std::uint64_t>(*this));
	}

	int packed_guid::high() const noexcept
	{
		return static_cast<int>(static_cast<std::uint64_t>(*this) >> 32);
	}

	wow::guid packed_guid::unpack() const noexcept
	{
		return static_cast<wow::guid>(*this);
	}

	packed_guid::operator std::uint64_t() const noexcept
	{
		return static_cast<std::uint64_t>(static_cast<wow::guid>(*this));
	}

	packed_guid::operator wow::guid() const noexcept
	{
		return guid_;
	}
}
