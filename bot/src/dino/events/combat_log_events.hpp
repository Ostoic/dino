#pragma once

#include "../wow/data/store.hpp"
#include "../wow/offsets.hpp"

#include <boost/mp11/list.hpp>

namespace dino::events
{
	struct received_combat_log_multiple
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_combat_log_multiple_fn;
		static constexpr auto event_id = wow::net::messages::server::combat_log_multiple;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_periodic_aura_log
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_periodic_aura_log_fn;
		static constexpr auto event_id = wow::net::messages::server::periodic_aura_log;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_non_melee_damage_log
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_non_melee_damage_log_fn;
		static constexpr auto event_id = wow::net::messages::server::spell_non_melee_damage_log;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_log_execute
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_log_execute_fn;
		static constexpr auto event_id = wow::net::messages::server::spell_log_execute;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_log_miss
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_log_miss_fn;
		static constexpr auto event_id = wow::net::messages::server::spell_log_miss;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_heal_log
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_heal_log_fn;
		static constexpr auto event_id = wow::net::messages::server::spell_heal_log;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_energize_log
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_energize_log_fn;
		static constexpr auto event_id = wow::net::messages::server::spell_energize_log;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_break_log
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_break_log;
		static constexpr auto event_id = wow::net::messages::server::spell_break_log;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_dispell_log
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_dispell_log;
		static constexpr auto event_id = wow::net::messages::server::spell_dispell_log;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	struct received_spell_steal_log
	{
		static constexpr auto packet_handler = wow::offsets::net::messages::packet_smsg_spell_steal_log;
		static constexpr auto event_id = wow::net::messages::server::spell_steal_log;

		mutable wow::data::store store;
		mutable bool* drop_packet;
	};

	using combat_log_events = boost::mp11::mp_list<
		received_spell_steal_log,
		received_spell_dispell_log,
		received_spell_break_log,
		received_spell_energize_log,
		received_spell_heal_log,
		received_spell_log_miss,
		received_spell_log_execute,
		received_spell_non_melee_damage_log,
		received_periodic_aura_log,
		received_combat_log_multiple
	>;
}