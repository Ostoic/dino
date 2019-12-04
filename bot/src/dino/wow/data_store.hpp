#pragma once

#include <cstddef>

#include "../offset.hpp"

namespace dino::wow
{
	class data_store
	{
	public:
		template <class From, class To>
		static constexpr bool is_compatible_v
			= std::is_convertible_v<From, To> && sizeof(From) == sizeof(To);

	public:
		explicit data_store(address class_base);

		const data_store* operator->() const
		{
			return this;
		}

		data_store* operator->()
		{
			return this;
		}

	public:
		std::size_t size() const;

		address base() const;
		unsigned int cursor() const;
		void set_cursor(unsigned int cursor);

		void restore_cursor();

		char* buffer();

		template <class T, class... Args>
		T pull(Args&&... args)
		{
			if constexpr (std::is_floating_point_v<T>)
				return static_cast<T>(this->pull_float());

			else if constexpr (std::is_same_v<T, char*>)
				return this->pull_string_ptr(std::forward<Args>(args)...);

			else if constexpr (std::is_same_v<T, std::string>)
				return this->pull_string(std::forward<Args>(args)...);

			else if constexpr (data_store::is_compatible_v<T, std::int64_t>)
				return static_cast<T>(this->pull_int64());

			else if constexpr (data_store::is_compatible_v<T, std::int32_t>)
				return static_cast<T>(this->pull_int32());

			else if constexpr (data_store::is_compatible_v<T, std::int16_t>)
				return static_cast<T>(this->pull_int16());

			else if constexpr (data_store::is_compatible_v<T, std::int8_t>)
				return static_cast<T>(this->pull_int8());

			else
				static_assert(false, "[wow::data_store::pull] Type is unsupported");
		}

		template <class T>
		void put(T x)
		{
			this->generic_put<T>(0, x);
		}

	private:
		template <class T>
		T generic_pull(const address fn_location)
		{
			const auto internal_pull = reinterpret_cast<void(__fastcall*)(void*, void*, T*)>(
				static_cast<unsigned int>(fn_location)
			);

			auto result = T{};
			internal_pull(
				reinterpret_cast<void*>(static_cast<unsigned int>(class_base_)),
				nullptr,
				&result
			);

			return result;
		}

		template <class T>
		void generic_put(const address fn_location, T x)
		{
			deref_as<T>(&this->buffer()[this->cursor()] - this->base()) = x;
		}

		float pull_float();
		std::int64_t pull_int64();
		std::int32_t pull_int32();
		std::int16_t pull_int16();
		std::int8_t pull_int8();
		char* pull_string_ptr(std::size_t max_length);
		std::string pull_string(std::size_t max_length = 64);

		void put_float(float value);
		void put_int64(std::int64_t value);
		void put_int32(std::int32_t value);
		void put_int16(std::int16_t value);
		void put_int8(std::int8_t value);
		//void put_string(std::string value);

	private:
		static constexpr std::size_t ingame_class_size = 24;

		address class_base_;
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