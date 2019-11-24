#pragma once

#include <string>

namespace dino::wow::glue::realmlist
{
	bool is_visible();

	void select_realm(const std::string& name);
	void select_realm(unsigned int index);

	std::string current_realm();
}
