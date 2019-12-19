#pragma once

#include "../wow/data/cast_failed_store.hpp"
#include "../wow/data/mount_result_store.hpp"

#include "../wow/net/messages.hpp"
#include "../wow/offsets.hpp"

#include <boost/mp11/list.hpp>

namespace dino::events
{
	struct received_cast_failed
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_cast_failed_fn;
		static constexpr auto event_id = wow::net::messages::server::cast_failed;

		mutable wow::data::cast_failed_store store;
		mutable bool* drop_packet;
	};

	struct received_mount_result
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_mount_result_fn;
		static constexpr auto event_id = wow::net::messages::server::mount_result;

		mutable wow::data::mount_result_store store;
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

	using spell_events = boost::mp11::mp_list<
		received_cast_failed,
		received_mount_result,
		received_unit_spellcast_start,
		received_spell_start,
		received_spell_go,
		received_spell_failure,
		received_spell_failed_other,
		received_spell_cooldown
	>;
}