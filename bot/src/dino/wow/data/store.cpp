#include "store.hpp"

#include "../offsets.hpp"
#include "../console.hpp"
#include "packed_guid.hpp"
#include "CDataStore.hpp"

#include "../../log.hpp"

namespace dino::wow::data
{
	store& store::operator=(const store& other) noexcept
	{
		store_ = other.store_;
		initial_cursor_ = other.initial_cursor_;
		return *this;
	}

	const store* store::operator->() const noexcept
	{
		return this;
	}

	store* store::operator->() noexcept
	{
		return this;
	}

	store::store(CDataStore* cdata_store, unsigned int initial_cursor)
		: store_{cdata_store}
		, initial_cursor_{initial_cursor}
	{}

	store::store(address base)
		: store{base, 2}
	{
		initial_cursor_ = this->cursor();
	}

	store::store(address class_base, unsigned int cursor)
		: store{reinterpret_cast<CDataStore*>(static_cast<address::address_type>(class_base)), cursor}
	{}

	store::store(store&& store)
		: store{store.store_, store->cursor()}
	{}

	store::store(const store& store, unsigned int initial_cursor)
		: store{store.store_, initial_cursor}
	{}

	store::~store()
	{
		this->restore_cursor();
	}

	std::size_t store::size() const
	{
		return store_->m_size;
	}

	address store::class_base()
	{
		return store_;
	}

	address store::base() const
	{
		return store_->m_base;
	}

	std::size_t store::cursor() const
	{
		return store_->m_cursor;
	}

	void store::seek(unsigned int cursor)
	{
		store_->m_cursor = cursor;
	}

	void store::seek_end()
	{
		this->seek(this->size() - 1);
	}

	void store::restore_cursor()
	{
		this->seek(initial_cursor_);
	}

	char* store::buffer()
	{
		return reinterpret_cast<char*>(store_->m_buffer);
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

	float store::pull_float()
	{
		float result;
		store_->GetFloat(&result);
		return result;
	}

	data::packed_guid store::pull_packed_guid()
	{
		guid result;
		store_->GetPackedGUID(&result);
		return packed_guid{std::move(result)};
	}

	std::int64_t store::pull_int64()
	{
		std::int64_t result;
		store_->GetInt64(&result);
		return result;
	}

	std::int32_t store::pull_int32()
	{
		std::int32_t result;
		store_->GetInt32(&result);
		return result;
	}

	std::int16_t store::pull_int16()
	{
		std::int16_t result;
		store_->GetInt16(&result);
		return result;
	}

	std::int8_t store::pull_int8()
	{
		std::int8_t result;
		store_->GetInt8(&result);
		return result;
	}

	char* store::pull_string_ptr(const std::size_t max_length)
	{
		char* ptr = nullptr;
		store_->GetStringPtr(&ptr, max_length);
		return ptr;
	}

	std::string store::pull_string(const std::size_t max_length)
	{
		std::string data;
		data.resize(max_length, 0);

		store_->GetString(data.data(), max_length);
		return std::string{data};
	}
}