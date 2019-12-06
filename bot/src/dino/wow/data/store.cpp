#include "store.hpp"

#include "../offsets.hpp"
#include "../console.hpp"
#include "compressed_guid.hpp"

namespace dino::wow::data
{
	const store* store::operator->() const noexcept
	{
		return this;
	}

	store* store::operator->() noexcept
	{
		return this;
	}

	store::store(address base)
		: class_base_{base}
	{
		initial_cursor_ = this->cursor();
	}

	store::store(address class_base, unsigned int cursor)
		: store{class_base}
	{
		initial_cursor_ = cursor;
	}

	store::store(const store& store, unsigned int initial_cursor)
		: store{store.class_base_, initial_cursor}
	{}

	std::size_t store::size() const
	{
		return deref_as<unsigned int>(class_base_ + offsets::store::size);
	}

	address store::class_base()
	{
		return class_base_;
	}

	address store::base() const
	{
		return deref_as<address>(class_base_ + offsets::store::base);
	}

	std::size_t store::cursor() const
	{
		return deref_as<unsigned int>(class_base_ + offsets::store::bytes_pulled);
	}

	void store::seek(unsigned int cursor)
	{
		auto& bytes_pulled = deref_as<unsigned int>(class_base_ + offsets::store::bytes_pulled);
		bytes_pulled = cursor;
	}

	void store::restore_cursor()
	{
		this->seek(initial_cursor_);
	}

	char* store::buffer()
	{
		return deref_as<char*>(class_base_ + offsets::store::buffer);
	}

	float store::pull_float()
	{
		return this->generic_pull<float>(offsets::store::get_float);
	}

	data::compressed_guid store::pull_compressed_guid()
	{
		return data::compressed_guid{*this};
	}

	void store::put_float(const float value)
	{
		this->generic_put<float>(offsets::store::put_float, value);
	}

	void store::put_int64(const std::int64_t value)
	{
		this->generic_put<std::int64_t>(offsets::store::put_int64, value);
	}

	void store::put_int32(const std::int32_t value)
	{
		this->generic_put<std::int32_t>(offsets::store::put_int32, value);
	}

	void store::put_int16(const std::int16_t value)
	{
		this->generic_put<std::int16_t>(offsets::store::put_int16, value);
	}

	void store::put_int8(const std::int8_t value)
	{
		this->generic_put<std::int8_t>(offsets::store::put_int8, value);
	}

	//void store::put_string(const std::string value)
	//{
	//	//this->generic_put<float>(offsets::store::put_float, value);
	//}

	std::int64_t store::pull_int64()
	{
		return this->generic_pull<std::int64_t>(offsets::store::get_int64);
	}

	std::int32_t store::pull_int32()
	{
		return this->generic_pull<std::int32_t>(offsets::store::get_int32);
	}

	std::int16_t store::pull_int16()
	{
		return this->generic_pull<std::int32_t>(offsets::store::get_int16);
	}

	std::int8_t store::pull_int8()
	{
		return this->generic_pull<std::int8_t>(offsets::store::get_int8);
	}

	char* store::pull_string_ptr(const std::size_t max_length)
	{
		const auto internal_pull = reinterpret_cast<void(__fastcall*)(void*, void*, char**, unsigned int)>(
			static_cast<unsigned int>(offsets::store::get_string_ptr)
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

	std::string store::pull_string(const std::size_t max_length)
	{
		const auto internal_pull = reinterpret_cast<void(__fastcall*)(void*, void*, char*, unsigned int)>(
			static_cast<unsigned int>(offsets::store::get_string)
		);

		std::string data;
		data.resize(max_length, 0);

		internal_pull(
			reinterpret_cast<void*>(static_cast<unsigned int>(class_base_)),
			nullptr,
			data.data(),
			static_cast<unsigned int>(max_length)
		);

		return std::string{data.data()};
	}
}