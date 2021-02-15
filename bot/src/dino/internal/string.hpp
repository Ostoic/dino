#pragma once

#include <string>

namespace dino::internal
{ 
	template <class LeftIt, class RightIt>
	std::string format_bytes(LeftIt begin, const RightIt end)
	{
		std::string bytes_string;
		for (auto it = begin; it != end; ++it)
		{
			if (it == begin)
				bytes_string += std::string{"byte(" + std::to_string(static_cast<unsigned int>(*it))} + ")";
			else
				bytes_string += ", " + std::string{"byte(" + std::to_string(static_cast<unsigned int>(*it))} + ")";
		}

		return bytes_string;
	}

	template <class Range>
	std::string format_bytes(const Range& bytes)
	{
		return format_bytes(std::begin(bytes), std::end(bytes));
	}
}
