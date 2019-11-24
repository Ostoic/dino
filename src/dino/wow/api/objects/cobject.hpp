#pragma once

#include "../../../offset.hpp"
#include "../../guid.hpp"

namespace dino::wow::objects
{
	class cobject
	{
	public:
		guid guid() const
		{
			return guid_;
		}

		virtual ~cobject() = default;

	private:
		explicit cobject(address base)
			: base_{base}
			, guid_{bind_value<wow::guid>(base)}
		{}

	private:
		address base_;
		wow::guid guid_;
	};


}