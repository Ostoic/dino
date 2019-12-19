#pragma once

#include <cstdint>
#include <iostream>

namespace dino::wow
{
	class guid
	{
	public:
		constexpr guid();
		constexpr explicit guid(int low, int high);
		constexpr explicit guid(std::uint64_t value);
		constexpr int low() const noexcept;
		constexpr int high() const noexcept;
		explicit guid(std::string value);

		constexpr operator std::uint64_t() const noexcept;

	private:
		int low_;
		int high_;
	};

}

inline std::ostream& operator<<(std::ostream& out, const dino::wow::guid& guid)
{
	out << fmt::format("{:#08x}", static_cast<std::uint64_t>(guid));
	return out;
}

namespace dino::wow
{
	constexpr guid::guid()
		: low_{0}
		, high_{0}
	{}

	constexpr guid::guid(int low, int high)
		: low_{low}
		, high_{high}
	{}

	constexpr guid::guid(const std::uint64_t value)
		: low_{static_cast<int>(value)}
		, high_{static_cast<int>(value >> 32)}
	{}

	constexpr int guid::low() const noexcept
	{
		return static_cast<int>(low_);
	}

	constexpr int guid::high() const noexcept
	{
		return static_cast<int>(high_);
	}

	constexpr guid::operator std::uint64_t() const noexcept
	{
		return static_cast<std::uint64_t>(low_) | (static_cast<std::uint64_t>(high_) << 32);
	}
}
