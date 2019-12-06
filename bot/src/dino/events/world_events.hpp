#pragma once

#include "../wow/data/new_world_store.hpp"
#include "../wow/data/cast_failed_store.hpp"
#include "../wow/data/ai_reaction_store.hpp"
#include "../wow/data/mount_result_store.hpp"
#include "../wow/data/health_update_store.hpp"
#include "../wow/data/cooldown_cheat_store.hpp"

#include "../wow/net/messages.hpp"
#include "../wow/offsets.hpp"

namespace dino::events
{
	struct received_new_world
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_new_world_fn;
		static constexpr auto event_id = wow::net::messages::server::new_world;

		mutable wow::data::new_world_store store;
		mutable bool* drop_packet;
	};

	struct received_cast_failed
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_cast_failed_fn;
		static constexpr auto event_id = wow::net::messages::server::cast_failed;

		mutable wow::data::cast_failed_store store;
		mutable bool* drop_packet;
	};

	struct received_health_update
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_health_update_fn;
		static constexpr auto event_id = wow::net::messages::server::health_update;

		mutable wow::data::health_update_store store;
		mutable bool* drop_packet;
	};

	struct received_cooldown_cheat
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_cooldown_cheat_fn;
		static constexpr auto event_id = wow::net::messages::server::cooldown_cheat;

		mutable wow::data::cooldown_cheat_store store;
		mutable bool* drop_packet;
	};

	struct received_ai_reaction
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_ai_reaction_fn;
		static constexpr auto event_id = wow::net::messages::server::ai_reaction;

		mutable wow::data::ai_reaction_store store;
		mutable bool* drop_packet;
	};

	struct received_mount_result
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_mount_result_fn;
		static constexpr auto event_id = wow::net::messages::server::mount_result;

		mutable wow::data::mount_result_store store;
		mutable bool* drop_packet;
	};

	struct received_loot_list
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_loot_list_fn;
		static constexpr auto event_id = wow::net::messages::server::loot_list;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_update_object
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_update_object_fn;
		static constexpr auto event_id = wow::net::messages::server::update_object;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_stand_state_update
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_stand_state_update_fn;
		static constexpr auto event_id = wow::net::messages::server::stand_state_update;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_unit_spellcast_start
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_unit_spellcast_start_fn;
		static constexpr auto event_id = wow::net::messages::server::unit_spellcast_start;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_start
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_start_fn;
		static constexpr auto event_id = wow::net::messages::server::spell_start;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_go
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_go_fn;
		static constexpr auto event_id = wow::net::messages::server::spell_go;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_failure
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_failure_fn;
		static constexpr auto event_id = wow::net::messages::server::spell_failure;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_failed_other
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_failed_other_fn;
		static constexpr auto event_id = wow::net::messages::server::spell_failed_other;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_cooldown
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_cooldown_fn;
		static constexpr auto event_id = wow::net::messages::server::spell_cooldown;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_notification
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_notification;
		static constexpr auto event_id = wow::net::messages::server::notification;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};
}