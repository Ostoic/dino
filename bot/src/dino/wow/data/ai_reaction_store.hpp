#pragma once

#include "store.hpp"
#include "../guid.hpp"

namespace dino::wow::data
{
	struct ai_reaction_store : public store
	{
	public:
		template <class... Args>
		explicit ai_reaction_store(Args&&... args)
			: store{std::forward<Args>(args)}
		{}

	public:
		void set_agent(guid agent);
		void set_flags(unsigned int flags);

		guid agent() const;
		unsigned int flags() const;
	};
}
