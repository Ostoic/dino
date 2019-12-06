#include "ai_reaction_store.hpp"

namespace dino::wow::data
{
	ai_reaction_store::ai_reaction_store(address store_base)
		: ai_reaction_store{data::store{store_base}}
	{}

	ai_reaction_store::ai_reaction_store(data::store store)
		: store_{store}
	{
		store_->restore_cursor();
	}

	ai_reaction_store* ai_reaction_store::operator->() noexcept
	{
		return this;
	}

	const ai_reaction_store* ai_reaction_store::operator->() const noexcept
	{
		return this;
	}

	void ai_reaction_store::set_agent(const guid receiver)
	{
		store_->put(receiver);
		store_->restore_cursor();
	}

	void ai_reaction_store::set_flags(const unsigned int flags)
	{
		store_->pull<guid>();
		store_->put(flags);
		store_->restore_cursor();
	}

	guid ai_reaction_store::agent() const
	{
		const auto result = store_->pull<guid>();
		store_->restore_cursor();
		return result;
	}
	unsigned int ai_reaction_store::flags() const
	{
		store_->pull<guid>();
		const auto result = store_->pull<unsigned int>();
		store_->restore_cursor();
		return result;
	}
}