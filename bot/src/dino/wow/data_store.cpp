#include "data_store.hpp"

#include "offsets.hpp"
#include "console.hpp"

namespace dino::wow
{
	data_store::data_store(address base)
		: class_base_{base}
	{
		initial_cursor_ = this->cursor();
	}

	std::size_t data_store::size() const
	{
		return deref_as<unsigned int>(class_base_ + offsets::data_store::size);
	}

	address data_store::base() const
	{
		return deref_as<address>(class_base_ + offsets::data_store::base);
	}

	std::size_t data_store::cursor() const
	{
		return deref_as<unsigned int>(class_base_ + offsets::data_store::bytes_pulled);
	}

	void data_store::set_cursor(unsigned int cursor)
	{
		auto& bytes_pulled = deref_as<unsigned int>(class_base_ + offsets::data_store::bytes_pulled);
		bytes_pulled = cursor;
	}

	void data_store::restore_cursor()
	{
		this->set_cursor(initial_cursor_);
	}

	char* data_store::buffer()
	{
		return deref_as<char*>(class_base_ + offsets::data_store::buffer);
	}

	float data_store::pull_float()
	{
		return this->generic_pull<float>(offsets::data_store::get_float);
	}

	void data_store::put_float(const float value)
	{
		this->generic_put<float>(offsets::data_store::put_float, value);
	}

	void data_store::put_int64(const std::int64_t value)
	{
		this->generic_put<std::int64_t>(offsets::data_store::put_int64, value);
	}

	void data_store::put_int32(const std::int32_t value)
	{
		this->generic_put<std::int32_t>(offsets::data_store::put_int32, value);
	}

	void data_store::put_int16(const std::int16_t value)
	{
		this->generic_put<std::int16_t>(offsets::data_store::put_int16, value);
	}

	void data_store::put_int8(const std::int8_t value)
	{
		this->generic_put<std::int8_t>(offsets::data_store::put_int8, value);
	}

	//void data_store::put_string(const std::string value)
	//{
	//	//this->generic_put<float>(offsets::data_store::put_float, value);
	//}

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

	char* data_store::pull_string_ptr(const std::size_t max_length)
	{
		const auto internal_pull = reinterpret_cast<void(__fastcall*)(void*, void*, char**, unsigned int)>(
			static_cast<unsigned int>(offsets::data_store::get_string_ptr)
		);

		char* data = nullptr;
		internal_pull(
			reinterpret_cast<void*>(static_cast<unsigned int>(class_base_)),
			nullptr,
			&data,
			static_cast<unsigned int>(max_length)
		);

		return data;
	}

	std::string data_store::pull_string(const std::size_t max_length)
	{
		const auto internal_pull = reinterpret_cast<void(__fastcall*)(void*, void*, char*, unsigned int)>(
			static_cast<unsigned int>(offsets::data_store::get_string)
		);

		std::string data;
		data.resize(max_length);

		internal_pull(
			reinterpret_cast<void*>(static_cast<unsigned int>(class_base_)),
			nullptr,
			data.data(),
			static_cast<unsigned int>(max_length)
		);

		return data;
	}
}