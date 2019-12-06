#pragma once

#include "../offset.hpp"

namespace dino::wow::offsets
{
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

	namespace game
	{
		constexpr auto root_path = address{0x00B32360};
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

	namespace object_manager
	{
	}

	namespace time
	{
		constexpr auto timestamp = address{0x00B1D618};
		constexpr auto last_action = address{0x00B499A4};
	}

	namespace world
	{
		constexpr auto traceline_fn = address{0x007A3B70};
		constexpr auto get_framerate_fn = address{0x0077F440};

		constexpr auto is_valid_position_fn = address{0x00406E90};
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
		constexpr auto get_compressed_guid = address{0x0076DC20};
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

			constexpr auto packet_msg_raid_target_update_fn = address{0x005743B0};
		}

		namespace client_services
		{
			constexpr auto nc_set_message_handler_fn = address{0x00631FA0};
			constexpr auto set_message_handler_fn = address{0x006B0B80};
			constexpr auto clear_message_handler_fn = address{0x006B0BC0};

			constexpr auto singleton = address{0x00C79CF4};
		}
	}


	namespace dx
	{
		constexpr auto device_ptr_base = address{0x00C5DF88};
		constexpr auto device_ptr_off = address{0x397C};

		constexpr auto beginscene_off = address{0xA4};
		constexpr auto endscene_off = address{0xA8};
	}
}
