#include "data_store.hpp"

#include "offsets.hpp"
#include "console.hpp"

namespace dino::wow
{
	data_store::data_store(address base)
		: base_{base}
	{}

	std::size_t data_store::size() const
	{
		console::dino("[data_store::size] test");
		return deref_as<unsigned int>(base_ + offsets::data_store::size);
	}

	std::size_t data_store::cursor() const
	{
		return deref_as<unsigned int>(base_ + offsets::data_store::bytes_pulled);
	}

	void data_store::set_cursor(unsigned int cursor)
	{
		deref_as<unsigned int>(base_ + offsets::data_store::bytes_pulled) = cursor;
	}

	void __stdcall test(int x)
	{
		console::dino("x = {}", x);
	}

	float data_store::pull_float()
	{
		return this->generic_pull<float>(offsets::data_store::get_float);
	}

	std::int64_t data_store::pull_int64()
	{
		return this->generic_pull<std::int64_t>(offsets::data_store::get_int64);
	}

	std::int32_t data_store::pull_int32()
	{
		return this->generic_pull<std::int32_t>(offsets::data_store::get_int32);
	}

	std::int16_t data_store::pull_int16()
	{
		return this->generic_pull<std::int32_t>(offsets::data_store::get_int16);
	}

	std::int8_t data_store::pull_int8()
	{
		return this->generic_pull<std::int8_t>(offsets::data_store::get_int8);
	}

	std::string data_store::pull_string()
	{
		//const auto internal_pull = reinterpret_cast<void(__fastcall*)(void*, void*, *)>(
		//	static_cast<unsigned int>(offsets::data_store::get_string_count)
		//	);

		//internal_pull(
		//	reinterpret_cast<void*>(static_cast<unsigned int>(base_)),
		//	nullptr,
		//	&result
		//);

		//return result;
		return {};
	}
}