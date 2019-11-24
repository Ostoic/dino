#pragma once

#include <cstdint>

namespace dino::wow
{
	class guid
	{
	public:
		constexpr explicit guid(int low, int high);
		constexpr int low() const noexcept;
		constexpr int high() const noexcept;

		constexpr operator std::int64_t() const noexcept;

	private:
		std::int64_t value_;
	};


	constexpr guid::guid(int low, int high)
		: value_{(static_cast<int64_t>(high) << 32) | static_cast<int64_t>(low)}
	{}

	constexpr int guid::low() const noexcept
	{
		return static_cast<int>(value_);
	}

	constexpr int guid::high() const noexcept
	{
		return static_cast<int>(value_ >> 32);
	}

	constexpr guid::operator std::int64_t() const noexcept
	{
		return value_;
	}
}
