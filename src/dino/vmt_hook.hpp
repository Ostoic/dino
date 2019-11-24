#pragma once

#include "offset.hpp"

namespace dino
{


	template <class Fn>
	class vmt_hook
	{
	public:
		explicit vmt_hook(address pointer_location, Fn&& hook_fn)
			: original_{pointer_location}
			, hook_fn_{hook_fn}
		{}

	private:
		void hook()
		{

		}

		void unhook()
		{

		}

	private:
		address original_;
		fn_ptr<Fn> hook_fn_;
	};
}
