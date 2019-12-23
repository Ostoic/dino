#include "ai_reaction_store.hpp"

namespace dino::wow::data
{
	void ai_reaction_store::set_agent(const guid receiver)
	{
		this->put(receiver);
		this->restore_cursor();
	}

	void ai_reaction_store::set_flags(const unsigned int flags)
	{
		this->pull<wow::guid>();
		this->put(flags);
		this->restore_cursor();
	}

	guid ai_reaction_store::agent() const
	{
		auto* store = const_cast<ai_reaction_store*>(this);
		const auto result = store->pull<wow::guid>();
		store->restore_cursor();
		return guid{result};
	}
	unsigned int ai_reaction_store::flags() const
	{
		auto* store = const_cast<ai_reaction_store*>(this);
		store->pull<wow::guid>();
		const auto result = store->pull<unsigned int>();
		store->restore_cursor();
		return result;
	}
}