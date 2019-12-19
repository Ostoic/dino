#pragma once

//#include "object_iterator.hpp"

#include "../offsets.hpp"
#include "../guid.hpp"

namespace dino::wow::world
{
	class entity_manger
	{
	public:
		//using iterator = object_iterator;
		//using const_iterator = object_iterator;

	public:
		//iterator begin();
		//iterator end();
		//const_iterator begin() const;
		//const_iterator end() const;

		//const_iterator cbegin() const;
		//const_iterator cend() const;

	private:
	};

	address local_base();
	guid local_guid();
}
