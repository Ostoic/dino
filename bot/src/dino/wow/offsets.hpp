#pragma once

#include "../offset.hpp"

namespace dino::wow::offsets
{
	namespace account
	{
		constexpr auto name = address{0x00B6AA40};
	}

	namespace console
	{
		constexpr auto enabled = address{0x00CABCC4};
		constexpr auto active = address{0x00CA1978};
		constexpr auto num_lines = address{0x00CA197C};

		constexpr auto keybind = address{0x00ADBAC4};

		constexpr auto write_fn = address{0x00765270};
		constexpr auto register_fn = address{0x00769100};
		constexpr auto clear_fn = address{0x007644B0};

		constexpr auto last_line = address{0x00CABA58};
	}

	namespace guild
	{
		constexpr auto num_total_members = address{0x00C22AB0};
		constexpr auto num_online_members = address{0x00C22AB4};
		constexpr auto roster_list = address{0x00C22AE0};
	}

	namespace game
	{
		constexpr auto root_path = address{0x00B32360};
	}

	namespace navigation
	{
		constexpr auto click_to_move_fn = address{0x00727400};

	}

	namespace lua
	{
		constexpr auto stack = address{0x00D3F78C};
		constexpr auto framescript_execute_fn = address{0x00819210};
		constexpr auto framescript_get_text_fn = address{0x00819D40};
		constexpr auto framcescript_register_function_fn = address{0x00817F90};
	}

	namespace chat
	{
		constexpr auto add_chat_message_fn = address{0x00509DD0};
	}

	namespace db
	{
		constexpr auto is_compressed = address{0x00C5DEA0};

		constexpr auto areas = address{0x00AD3134};
		constexpr auto character_classes = address{0x00AD3404};
		constexpr auto power_display = address{0x00AD43A0};
	}

	namespace guid
	{
		constexpr auto string_to_guid = address{0x0074D120};
	}

	namespace world
	{
		constexpr auto ingame = address{0x00BEBA40};

		constexpr auto traceline_fn = address{0x007A3B70};
		constexpr auto trace_count = address{0x00CE04C4};

		constexpr auto get_framerate_fn = address{0x0077F440};

		constexpr auto is_valid_position_fn = address{0x00406E90};

		constexpr auto time_mgr_singleton = address{0x00D4159C};
		constexpr auto get_async_time_ms_fn = address{0x0086AE20};

		namespace entity_manager
		{
			constexpr auto get_local_base_fn = address{0x004038F0};
			constexpr auto get_local_guid_fn = address{0x004D3790};
		}

		namespace entities
		{
			namespace object
			{

			}

			namespace game_object
			{

			}

			namespace unit
			{
				constexpr auto get_creature_type_fn = address{0x0071F300};
				constexpr auto write_movement_packet_with_transport_fn = address{0x0071F0C0};

				constexpr auto update_display_fn = address{0x0073E410};
				constexpr auto update_mount_display_fn = address{0x00740450};

				constexpr auto send_movement_packet_fn = address{0x007413F0};
			}

			namespace player
			{

			}
		}

		namespace time
		{
			constexpr auto timestamp = address{0x00B1D618};
			constexpr auto last_action = address{0x00B499A4};

			constexpr auto timing_method_offset = address{0x8};

			constexpr auto singleton = address{0x00D4159C};
		}
	}

	namespace warden
	{
		constexpr auto mediv_mod = address{0x00AF16D8};
		constexpr auto mediv_key = address{0x00AF298C};

		constexpr auto base_ptr = address{0xD31A48};
		constexpr auto scan_member_fn_offset = address{0x2A95};
		constexpr auto class_ptr = address{0x00D31A4C};

		constexpr auto rc4_keys_offset = address{0x20};
		constexpr auto rc4_keys_size = address{0x102};

		constexpr auto singleton = address{0x00D31A44};

		constexpr auto load_time = address{0xD31A58};
	}

	namespace combat_log
	{
		constexpr auto add_combat_log_entry = address{0x00751C40};
	}

	namespace store
	{
		// offsets
		constexpr auto vtable = address{0x0};
		constexpr auto buffer = address{0x4};
		constexpr auto base = address{0x8};
		constexpr auto allocated_size = address{0xC};
		constexpr auto size = address{0x10};
		constexpr auto bytes_pulled = address{0x14};

		// pull functions
		constexpr auto get_int8 = address{0x0047B340};
		constexpr auto get_int16 = address{0x0047B380};
		constexpr auto get_int32 = address{0x0047B3C0};
		constexpr auto get_int64 = address{0x0047B400};
		constexpr auto get_float = address{0x0047B440};
		constexpr auto get_packed_guid = address{0x0076DC20};
		constexpr auto get_string = address{0x0047B480};
		constexpr auto get_string_ptr = address{0x0047B6B0};

		// put functions
		constexpr auto put_int8 = address{0x0047AFE0};
		constexpr auto put_int16 = address{0x0047B040};
		constexpr auto put_int32 = address{0x0047B0A0};
		constexpr auto put_int64 = address{0x0047B100};
		constexpr auto put_float = address{0x0047B160};
		constexpr auto put_cstring = address{0x0047B300};
	}

	namespace net
	{
		namespace messages
		{
			constexpr auto packet_smsg_messagechat_fn = address{0x0050EBA0};
			constexpr auto packet_smsg_gm_messagechat_fn = address{0x0050EBC0};
			constexpr auto packet_smsg_text_emote_fn = address{0x00504070};
			constexpr auto packet_smsg_cast_failed_fn = address{0X00809AF0};
			constexpr auto packet_smsg_dismount_fn = address{0x00741A40};
			constexpr auto packet_smsg_new_world_fn = address{0x00403D10};

			constexpr auto packet_smsg_loot_list_fn = address{0x0071CA50};
			constexpr auto packet_smsg_stand_state_update_fn = address{0x0073F540};
			constexpr auto packet_smsg_unit_spellcast_start_fn = address{0x008020C0};
			constexpr auto packet_smsg_spell_cooldown_fn = address{0x00806DD0};
			constexpr auto packet_smsg_spell_start_fn = address{0x0080FEE0};
			constexpr auto packet_smsg_spell_go_fn = address{0x0080FEE0};
			constexpr auto packet_smsg_spell_failure_fn = address{0x00809C70};
			constexpr auto packet_smsg_spell_failed_other_fn = address{0x00806AD0};

			constexpr auto packet_smsg_combat_log_multiple_fn = address{0x006D4110};
			constexpr auto packet_smsg_notification = address{0x00401280};

			constexpr auto packet_smsg_spell_log_execute_fn = address{0x006D3730};
			constexpr auto packet_smsg_spell_log_miss_fn = address{0x006D3200};
			constexpr auto packet_smsg_spell_damage_shield_fn = address{0x006D3750};
			constexpr auto packet_smsg_spell_instakill_log_fn = address{0x006CE260};
			constexpr auto packet_smsg_spell_non_melee_damage_log_fn = address{0x006D3C10};

			constexpr auto packet_smsg_debug_aura_proc_fn = address{0x006D3730};
			constexpr auto packet_smsg_periodic_aura_log_fn = address{0x006D3730};
			constexpr auto packet_smsg_spell_heal_log_fn = address{0x006D3DD0};
			constexpr auto packet_smsg_spell_energize_log_fn = address{0x006D3EF0};

			constexpr auto packet_smsg_spell_break_log = address{0x006CE3B0};
			constexpr auto packet_smsg_spell_steal_log = address{0x006CE3B0};
			constexpr auto packet_smsg_spell_dispell_log = address{0x006CE3B0};

			constexpr auto packet_smsg_health_update_fn = address{0x00716D20};
			constexpr auto packet_smsg_power_update_fn = address{0x007236C0};
			constexpr auto packet_smsg_guild_roster_fn = address{0x005CC5D0};

			constexpr auto packet_smsg_update_object_fn = address{0x004D73A0};
			constexpr auto packet_smsg_destroy_object_fn = address{0x004D7610};

			constexpr auto packet_smsg_ai_reaction_fn = address{0x00716B10};
			constexpr auto packet_smsg_cooldown_cheat_fn = address{0x00804110};

			constexpr auto packet_smsg_mount_result_fn = address{0x006e2e90};
			constexpr auto packet_smsg_dismount_result_fn = address{0x006e2e90};

			constexpr auto packet_smsg_durabilty_damage_death_fn_ptr = address{0x0050C810};

			constexpr auto packet_msg_raid_target_update_fn = address{0x005743B0};

			constexpr auto packet_smsg_zone_under_attack_fn = address{0x0050C3C0};
			constexpr auto packet_smsg_warden_data_fn = address{0x007DA850};
			constexpr auto packet_cmsg_warden_data_fn = address{0x007DAAB0};

			constexpr auto cmsg_warden_data_fn_ptr = address{0x00A40788};

			constexpr auto packet_smsg_server_message_fn = address{0x0050C9FC};
		}

		constexpr auto num_received_packets = address{0x00C5D638};
		constexpr auto num_sent_packets = address{0x00C5D62C};

		constexpr auto num_sent_bytes = address{0x00C5D628};
		constexpr auto num_received_bytes = address{0x00C5D634};

		namespace net_client
		{
			constexpr auto vtable = address{0x00A26D78};
			constexpr auto wc_connected = address{0x00632060};
			constexpr auto wc_disconnected = address{0x006326D0};
			constexpr auto wc_cant_connect = address{0x00632C10};
			constexpr auto wc_message_ready = address{0x00633330};
			constexpr auto handle_data_fn = address{0x00632460};

			constexpr auto set_message_handler_fn = address{0x00631FA0};
		}

		namespace realm_connection
		{
			constexpr auto vtable = address{0x009E8258};
		}

		namespace client_connection
		{
			constexpr auto vtable = address{0x00A307F8};
			constexpr auto singleton = address{0x00C79CE0};
		}

		namespace client_services
		{

			constexpr auto set_message_handler_fn = address{0x006B0B80};
			constexpr auto clear_message_handler_fn = address{0x006B0BC0};

			constexpr auto singleton = address{0x00C79CF4};
		}
	}

	namespace cvar
	{
		constexpr auto lookup_fn = address{0x00767440};
		constexpr auto set_fn = address{0x007668C0};

		constexpr auto default_value_offset = address{0x40};
		constexpr auto reset_offset = address{0x4C};
		constexpr auto data_offset = address{0x34};
		constexpr auto value_offset = address{0x28};
		constexpr auto name_offset = address{0x14};
	}

	namespace dx
	{
		constexpr auto device_ptr_base = address{0x00C5DF88};
		constexpr auto device_ptr_off = address{0x397C};

		constexpr auto beginscene_off = address{0xA4};
		constexpr auto endscene_off = address{0xA8};
	}
}
