#pragma once

#include "../../../offset.hpp"
#include "../../guid.hpp"

namespace dino::wow::world::entities
{
	class object
	{
	public:
		guid guid() const;
		virtual std::string name() const = 0;

	private:
		explicit object(address base);

	private:
		address base_;
		wow::guid guid_;
	};
}

namespace dino::wow::world::entities
{
	guid object::guid() const
	{
		return guid_;
	}

	object::object(const address base)
		: base_{base}
		, guid_{bind_value<wow::guid>(base)}
	{}
}