#include "CDataStore.hpp"

#include "../guid.hpp"
#include "../offsets.hpp"
#include "../../offset.hpp"

namespace dino::wow::data
{
	void CDataStore::GetPackedGUID(guid* guid)
	{
		// Note: This fn is not thiscall
		const auto& get_packed_guid
			= deref_as<void(CDataStore*, wow::guid*)>(wow::offsets::store::get_packed_guid);

		get_packed_guid(this, guid);
	}

	void CDataStore::GetString(char* out, unsigned int max_length)
	{
		const auto& get_string
			= dino::deref_as<CDataStore*(__fastcall)(CDataStore*, void*, char*, unsigned int)>(wow::offsets::store::get_string);

		get_string(this, nullptr, out, max_length);
	}

	void CDataStore::GetStringPtr(char** out, unsigned int max_length)
	{
		const auto& get_string_ptr
			= dino::deref_as<CDataStore*(__fastcall)(CDataStore*, void*, char**, unsigned int)>(wow::offsets::store::get_string_ptr);

		get_string_ptr(this, nullptr, out, max_length);
	}

	void CDataStore::GetFloat(float* out)
	{
		const auto& get_float
			= dino::deref_as<CDataStore*(__fastcall)(CDataStore*, void*, float*)>(wow::offsets::store::get_float);

		get_float(this, nullptr, out);
	}

	void CDataStore::GetInt8(std::int8_t* out)
	{
		const auto& get_int8
			= dino::deref_as<CDataStore*(__fastcall)(CDataStore*, void*, std::int8_t*)>(wow::offsets::store::get_int8);

		get_int8(this, nullptr, out);
	}

	void CDataStore::GetInt16(std::int16_t* out)
	{
		const auto& get_int16
			= dino::deref_as<CDataStore*(__fastcall)(CDataStore*, void*, std::int16_t*)>(wow::offsets::store::get_int16);

		get_int16(this, nullptr, out);
	}

	void CDataStore::GetInt32(std::int32_t* out)
	{
		const auto& get_int32
			= dino::deref_as<CDataStore*(__fastcall)(CDataStore*, void*, std::int32_t*)>(wow::offsets::store::get_int32);

		get_int32(this, nullptr, out);
	}

	void CDataStore::GetInt64(std::int64_t* out)
	{
		const auto& get_int64
			= dino::deref_as<CDataStore*(__fastcall)(CDataStore*, void*, std::int64_t*)>(wow::offsets::store::get_int64);

		get_int64(this, nullptr, out);
	}
}