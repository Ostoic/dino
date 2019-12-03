#pragma once

#include "../../offset.hpp"
#include "../guid.hpp"

namespace dino::wow::objects
{
	class object
	{
	public:
		guid guid() const;
		virtual std::string name() const = 0;

	private:
		explicit object(address base);

	private:
		address class_base_;
		wow::guid guid_;
	};


}

namespace dino::wow::objects
{
	guid object::guid() const
	{
		return guid_;
	}

	object::object(address base)
		: class_base_{base}
		, guid_{bind_value<wow::guid>(base)}
	{}
}