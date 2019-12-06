#pragma once

namespace dino::wow::geometry
{
	struct vector
	{
	public:
		constexpr vector(float x = 0, float y = 0, float z = 0) noexcept;

		constexpr float x() const noexcept;
		constexpr float y() const noexcept;
		constexpr float z() const noexcept;

		bool is_valid() const;

	private:
		float x_;
		float y_;
		float z_;
	};

	bool is_valid_position(const vector& vector);
}

namespace dino::wow::geometry
{
	constexpr vector::vector(float x, float y, float z) noexcept
		: x_{x}, y_{y}, z_{z}
	{}

	constexpr float vector::x() const noexcept
	{
		return x_;
	}

	constexpr float vector::y() const noexcept
	{
		return y_;
	}

	constexpr float vector::z() const noexcept
	{
		return z_;
	}
}