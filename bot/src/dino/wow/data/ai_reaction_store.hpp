#pragma once

#include "store.hpp"
#include "../guid.hpp"

namespace dino::wow::data
{
	struct ai_reaction_store
	{
	public:
		explicit ai_reaction_store(address store_base);
		explicit ai_reaction_store(data::store&& store);
		explicit ai_reaction_store(data::CDataStore* store);
		explicit ai_reaction_store() = default;

		ai_reaction_store* operator->() noexcept;
		const ai_reaction_store* operator->() const noexcept;

	public:
		void set_agent(guid agent);
		void set_flags(unsigned int flags);

		guid agent() const;
		unsigned int flags() const;

		void seek_end();

	private:
		mutable data::store store_;
	};
}