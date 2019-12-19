#pragma once

namespace dino::ai
{
	class model
	{
	public:
		explicit model();

	public:
		template <class Action>
		void simulate(Action&& action);

	private:

	};
}