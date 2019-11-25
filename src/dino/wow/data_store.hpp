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
		explicit data_store(address base);
		//data_store();

	public:
		std::size_t size() const;
		unsigned int cursor() const;
		void set_cursor(unsigned int cursor);

		template <class T>
		T pull()
		{
			if constexpr (std::is_floating_point_v<T>)
				return this->pull_float();

			else if constexpr (data_store::is_compatible_v<T, std::int64_t>)
				return this->pull_int64();

			else if constexpr (data_store::is_compatible_v<T, std::int32_t>)
				return this->pull_int32();

			else if constexpr (data_store::is_compatible_v<T, std::int16_t>)
				return this->pull_int16();

			else if constexpr (data_store::is_compatible_v<T, std::int8_t>)
				return this->pull_int8();

			else
			{
				static_assert(false, "[wow::data_store] Type is unsupported");
			}
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
				reinterpret_cast<void*>(static_cast<unsigned int>(base_)),
				nullptr,
				&result
			);

			return result;
		}

		float pull_float();
		std::int64_t pull_int64();
		std::int32_t pull_int32();
		std::int16_t pull_int16();
		std::int8_t pull_int8();
		std::string pull_string();

	private:
		static constexpr std::size_t ingame_class_size = 24;

		address base_;
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