#pragma once

#include <vector>
#include <functional>

namespace dino::ai
{
	class action
	{
	public:

	public:
		bool preconditions_satisfied() const;

		bool operator()();

	private:
		std::vector<std::function<bool()>> pre_conditions_;
		std::vector<std::function<bool()>> post_conditions_;
	};
}