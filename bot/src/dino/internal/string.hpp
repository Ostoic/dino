#pragma once

#include <string>
#include <sstream>

namespace dino::internal
{ 
	template <class LeftIt, class RightIt>
	std::string format_bytes(LeftIt begin, const RightIt end)
	{
		std::stringstream bytes_stream;
		for (auto it = begin; it != end; ++it)
		{
			if (it == begin)
				bytes_stream << "byte(" << static_cast<unsigned int>(*it) << ")";
			else
				bytes_stream << ", byte(" << static_cast<unsigned int>(*it) << ")";
		}

		return bytes_stream.str();
	}

	template <class Range>
	std::string format_bytes(const Range& bytes)
	{
		return format_bytes(std::begin(bytes), std::end(bytes));
	}
}
