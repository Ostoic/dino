#pragma once

//#include "model/model.hpp"

namespace dino::ai
{
	class agent
	{
		enum class state
		{
			idle,
			move_to,
			perform_action
		};

	public:
		// previous plans, previous objects of interest, etc
		int memory() const;

		void run();

	private:
		state state_;
	};
}