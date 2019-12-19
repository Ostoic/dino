#include "action.hpp"

#include <algorithm>

namespace dino::ai
{
	bool action::preconditions_satisfied() const
	{
		return std::all_of(pre_conditions_.begin(), pre_conditions_.end(), [](const auto& fn)
		{
			return fn();
		});
	}

	bool action::operator()()
	{
		if (!this->preconditions_satisfied())
			return false;

		// run action

		return true;
	}

}