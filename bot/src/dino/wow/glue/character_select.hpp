#pragma once

#include <string>

namespace dino::wow::glue::character_select
{
	unsigned int num_characters();

	void select_character(const std::string& name);
	void select_character(unsigned int index);
}
