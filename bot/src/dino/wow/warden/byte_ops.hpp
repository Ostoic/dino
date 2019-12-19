#pragma once

#include <vector>

namespace dino::wow::warden::rc4
{
	constexpr std::byte operator+(const std::byte lhs, const std::byte rhs)
	{
		return std::byte{static_cast<unsigned char>(lhs) + static_cast<unsigned char>(rhs)};
	}

	constexpr std::byte operator-(std::byte lhs, std::byte rhs)
	{
		return std::byte{static_cast<unsigned char>(lhs) - static_cast<unsigned char>(rhs)};
	}

	constexpr std::byte operator&(std::byte lhs, std::byte rhs)
	{
		return std::byte{static_cast<unsigned char>(lhs) & static_cast<unsigned char>(rhs)};
	}

	constexpr std::byte operator|(std::byte lhs, std::byte rhs)
	{
		return std::byte{static_cast<unsigned char>(lhs) | static_cast<unsigned char>(rhs)};
	}

	constexpr std::byte& operator+=(std::byte& lhs, std::byte rhs)
	{
		lhs = (lhs + rhs);
		return lhs;
	}

	constexpr std::byte& operator-=(std::byte& lhs, std::byte rhs)
	{
		lhs = (lhs - rhs);
		return lhs;
	}
}