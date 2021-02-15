#pragma once

#include <array>
#include "../offset.hpp"

namespace dino::hook
{
	class patch
	{
	public:
		patch(const patch&) = delete;
		patch& operator=(const patch&) = delete;

		patch(patch&& other);
		patch& operator=(patch&& other);

		explicit patch(address destination, std::vector<byte>&& data);

		template <unsigned int N>
		explicit patch(address destination, const std::array<byte, N>& data)
			: destination_{destination}
		{
			std::copy(data.begin(), data.end(), std::back_inserter(data_));
		}

		~patch()
		{
			if (destination_ != 0 && original_.size() > 0)
				this->restore();
		}

		void apply();
		void restore();

	private:
		address destination_;
		std::vector<byte> data_;
		std::vector<byte> original_;
	};
}