#pragma once

#include "../wow/data/new_world_store.hpp"
#include "../wow/data/cast_failed_store.hpp"
#include "../wow/data/ai_reaction_store.hpp"
#include "../wow/data/mount_result_store.hpp"
#include "../wow/data/health_update_store.hpp"
#include "../wow/data/cooldown_cheat_store.hpp"

namespace dino::events
{
	struct received_new_world
	{
		mutable wow::data::new_world_store store;
	};

	struct received_cast_failed
	{
		mutable wow::data::cast_failed_store store;
	};

	struct received_health_update
	{
		mutable wow::data::health_update_store store;
	};

	struct received_cooldown_cheat
	{
		mutable wow::data::cooldown_cheat_store store;
	};

	struct received_ai_reaction
	{
		mutable wow::data::ai_reaction_store store;
	};

	struct received_mount_result
	{
		mutable wow::data::mount_result_store store;
	};
}