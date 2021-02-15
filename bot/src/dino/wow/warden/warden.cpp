#include "warden.hpp"

#include "../offsets.hpp"
#include "../../log.hpp"

namespace dino::wow::warden
{
	bool is_loaded()
	{
		return warden::base() != 0;
	}

	address singleton()
	{
		return deref_as<address>(offsets::warden::singleton);
	}

	address scan_fn()
	{
		return warden::base() + offsets::warden::scan_member_fn_offset;
	}

	address base()
	{
		const auto module_loc = deref_as<address>(offsets::warden::base_ptr);
		if (module_loc == 0)
			return 0;

		return deref_as<address>(module_loc);
	}

	std::vector<byte> get_key_out()
	{
		const auto size = static_cast<address::address_type>(offsets::warden::rc4_keys_size);
		const auto class_loc = deref_as<address>(offsets::warden::class_ptr);
		const auto* key_bytes = &deref_as<const byte>(class_loc + offsets::warden::rc4_keys_offset);
		return std::vector<byte>{key_bytes, key_bytes + size};
	}

	std::vector<byte> get_key_in()
	{
		const auto size = static_cast<address::address_type>(offsets::warden::rc4_keys_size);
		const auto* key_bytes = deref_as<const byte*>(deref_as<address>(offsets::warden::class_ptr) + offsets::warden::rc4_keys_offset + offsets::warden::rc4_keys_size);

		return std::vector<byte>{key_bytes, key_bytes + size};
	}
}