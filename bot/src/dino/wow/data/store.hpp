#pragma once

#include <cstddef>

#include "../../offset.hpp"
#include "../guid.hpp"
#include "CDataStore.hpp"

namespace dino::wow::data
{
	class packed_guid;

	class store
	{
	public:
		template <class From, class To>
		static constexpr bool is_compatible_v
			= std::is_convertible_v<From, To> && sizeof(From) == sizeof(To);

	public:
		explicit store(CDataStore* cdata_store, unsigned int initial_cursor = 2);
		explicit store(address class_base);
		explicit store(address class_base, unsigned int cursor);
		explicit store(store&& store);
		explicit store(const store& store, unsigned int initial_cursor);
		explicit store() = default;

		~store();

		const store* operator->() const noexcept;
		store* operator->() noexcept;

	public:
		std::size_t size() const;

		address class_base();

		address base() const;
		unsigned int cursor() const;

		void seek(unsigned int cursor);

		void seek_end();

		void restore_cursor();

		char* buffer();

		template <class T, class... Args>
		T pull(Args&&... args)
		{
			if constexpr (std::is_floating_point_v<T>)
				return static_cast<T>(this->pull_float());

			else if constexpr (std::is_pointer_v<T>&& std::is_same_v<std::remove_cvref_t<std::remove_pointer_t<T>>, char>)
				return this->pull_string_ptr(std::forward<Args>(args)...);

			else if constexpr (std::is_same_v<T, std::string>)
				return this->pull_string(std::forward<Args>(args)...);

			else if constexpr (std::is_same_v<T, wow::guid>)
				return static_cast<T>(this->pull_int64());

			else if constexpr (std::is_same_v<T, wow::data::packed_guid>)
				return static_cast<T>(this->pull_packed_guid());

			else if constexpr (store::is_compatible_v<T, std::int64_t>)
				return static_cast<T>(this->pull_int64());

			else if constexpr (store::is_compatible_v<T, std::int32_t>)
				return static_cast<T>(this->pull_int32());

			else if constexpr (store::is_compatible_v<T, std::int16_t>)
				return static_cast<T>(this->pull_int16());

			else if constexpr (sizeof(T) == sizeof(std::int8_t))
				return static_cast<T>(this->pull_int8());

			else
				static_assert(false, "[wow::store::pull] Type is unsupported");
		}

		template <class T>
		void put(T x)
		{
			this->generic_put<T>(0, x);
		}

	private:
		template <class T>
		void generic_put(const address fn_location, T x)
		{
			deref_as<T>(&this->buffer()[this->cursor()] - this->base()) = x;
		}

		template <class T>
		T& pull_ref()
		{
			deref_as<T>(&this->buffer()[this->cursor()] - this->base());
		}

		float pull_float();
		packed_guid pull_packed_guid();
		std::int64_t pull_int64();
		std::int32_t pull_int32();
		std::int16_t pull_int16();
		std::int8_t pull_int8();
		char* pull_string_ptr(std::size_t max_length);
		std::string pull_string(std::size_t max_length = 64);

		void put_float(float value);
		void put_guid(wow::guid value);
		void put_int64(std::int64_t value);
		void put_int32(std::int32_t value);
		void put_int16(std::int16_t value);
		void put_int8(std::int8_t value);
		//void put_string(std::string value);

	private:
		static constexpr std::size_t ingame_class_size = 24;

		CDataStore* store_;
		unsigned int initial_cursor_;
	};
}

/*
struct CDataStore
{
  CDataStore_vTable *vTable;	// 0x00
  unsigned __int8 *m_buffer;	// 0x04
  unsigned int m_base;			// 0x08
  unsigned int m_alloc;			// 0x0C
  unsigned int m_size;			// 0x10
  unsigned int m_read;			// 0x14
};
*/