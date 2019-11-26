#pragma once

#include "object_iterator.hpp"

namespace dino::wow::objects
{
	class object_manager
	{
	public:
		//using iterator = object_iterator;
		//using const_iterator = object_iterator;

	public:
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		const_iterator cbegin() const;
		const_iterator cend() const;

	private:
	};
}
