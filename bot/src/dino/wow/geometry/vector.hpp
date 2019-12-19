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

	constexpr vector operator+(const vector& lhs, const vector& rhs) noexcept;
	constexpr vector operator-(const vector& lhs, const vector& rhs) noexcept;

	struct position : public vector
	{
		constexpr position(float x = 0, float y = 0, float z = 0, float rotation = 0) noexcept;

		constexpr float rotation() const noexcept;

	private:
		float rotation_;
	};

	bool is_valid_position(const vector& vector);

	vector front_of(const position& position, float magnitude = 1.0f);
}

namespace dino::wow::geometry
{
//vector:
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

	constexpr vector operator+(const vector& lhs, const vector& rhs) noexcept
	{
		return vector{
			lhs.x() + rhs.x(),
			lhs.y() + rhs.y(),
			lhs.z() + rhs.z()
		};
	}

	constexpr vector operator-(const vector& lhs, const vector& rhs) noexcept
	{
		return vector{
			lhs.x() - rhs.x(),
			lhs.y() - rhs.y(),
			lhs.z() - rhs.z()
		};
	}

//position:
	constexpr position::position(float x, float y, float z, float rotation) noexcept
		: vector{x, y, z}
		, rotation_{rotation}
	{}

	constexpr float position::rotation() const noexcept
	{
		return rotation_;
	}

}