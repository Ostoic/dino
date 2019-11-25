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

	namespace object_manager
	{
	}

	namespace time
	{

	}

	namespace world
	{

	}

	namespace data_store
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
		constexpr auto get_string = address{0x0047B480};
		constexpr auto get_string_count = address{0x0047B6B0};

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
		}

		namespace client_services
		{
			constexpr auto nc_set_message_handler_fn = address{0x00631FA0};
			constexpr auto set_message_handler_fn = address{0x006B0B80};

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
