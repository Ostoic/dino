#pragma once

#include <cstdint>
#include <boost/mp11.hpp>

namespace dino::internal
{
	template <std::uint64_t Max>
	class uuid_
	{
	public:
		constexpr uuid_() noexcept;

		constexpr uuid_(std::uint64_t value) noexcept;

		constexpr operator std::uint64_t() const noexcept;

	public:
		constexpr std::uint64_t next() noexcept;

	public:
		static constexpr auto max = Max;

	private:
		mutable std::uint64_t current_uuid_;
	};

	using uuid = uuid_<100>;
}

namespace dino::internal
{
	template <std::uint64_t Max>
	constexpr uuid_<Max>::uuid_() noexcept
		: current_uuid_{0}
	{}

	template <std::uint64_t Max>
	constexpr uuid_<Max>::uuid_(std::uint64_t value) noexcept
		: current_uuid_{value}
	{}

	template <std::uint64_t Max>
	constexpr uuid_<Max>::operator std::uint64_t() const noexcept
	{
		return current_uuid_;
	}

	template <std::uint64_t Max>
	constexpr std::uint64_t uuid_<Max>::next() noexcept
	{
		return current_uuid_++;
	}

}