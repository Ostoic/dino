#include "entity_manger.hpp"

#include "../../log.hpp"

namespace dino::wow::world
{
	address local_base()
	{
		log::info("[local_base] before");
		const auto& get_local_base = deref_as<address*()>(offsets::world::entity_manager::get_local_base_fn);
		log::info("[local_base] after");
		const auto result = *get_local_base();
		log::info("[local_base] after after");
		return result;
	}

	guid local_guid()
	{
		const auto& get_local_guid = deref_as<guid()>(offsets::world::entity_manager::get_local_guid_fn);
		return get_local_guid();
	}
}
