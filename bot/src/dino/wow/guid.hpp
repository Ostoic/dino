#pragma once

#include <cstdint>

namespace dino::wow
{
	class guid
	{
	public:
		constexpr guid();
		constexpr explicit guid(int low, int high);
		constexpr explicit guid(std::uint64_t value);
		constexpr explicit guid(std::int64_t value);
		constexpr int low() const noexcept;
		constexpr int high() const noexcept;

		constexpr operator std::uint64_t() const noexcept;

	private:
		std::uint64_t value_;
	};

	constexpr guid::guid()
		: value_{0}
	{}

	constexpr guid::guid(int low, int high)
		: value_{(static_cast<std::uint64_t>(high) << 32) | static_cast<std::uint64_t>(low)}
	{}

	constexpr guid::guid(const std::uint64_t value)
		: value_{value}
	{}

	constexpr guid::guid(const std::int64_t value)
		: value_{static_cast<std::uint64_t>(value)}
	{}

	constexpr int guid::low() const noexcept
	{
		return static_cast<int>(value_);
	}

	constexpr int guid::high() const noexcept
	{
		return static_cast<int>(value_ >> 32);
	}

	constexpr guid::operator std::uint64_t() const noexcept
	{
		return value_;
	}
}
