#include "compressed_guid.hpp"

#include "../offsets.hpp"
#include "../console.hpp"

namespace dino::wow::data
{
	compressed_guid::compressed_guid(const data::store store)
		: store_{store}
	{}

	int compressed_guid::low() const noexcept
	{
		return static_cast<int>(static_cast<std::uint64_t>(*this));
	}

	int compressed_guid::high() const noexcept
	{
		return static_cast<int>(static_cast<std::uint64_t>(*this) >> 32);
	}

	compressed_guid::operator std::uint64_t() const noexcept
	{
		return static_cast<std::uint64_t>(static_cast<wow::guid>(*this));
	}

	compressed_guid::operator wow::guid() const noexcept
	{
		const auto get_compressed_wow_guid = bind_fn<void(void*, wow::guid*)>(offsets::store::get_compressed_guid);

		auto guid = wow::guid{0};
		get_compressed_wow_guid(reinterpret_cast<void*>(static_cast<unsigned int>(store_.class_base())), &guid);
		return guid;
		//std::uint64_t guid_;
		//std::uint64_t* guid = &guid_;

		//int v2; // ebx@1
		//unsigned int v3; // edi@1
		//std::uint64_t* guid2; // esi@1
		//unsigned __int8 v5; // [sp+Fh] [bp-1h]@3

		//guid2 = guid;
		//v2 = 0;
		//*guid = wow::guid{0};
		//*(unsigned char*)(&guid + 3) = store_->pull<std::uint8_t>();
		//v3 = 0;
		//do
		//{
		//	if ((unsigned __int8)(1 << v2) & *(unsigned char*)(&guid + 3))
		//	{
		//		v5 = store_->pull<std::uint8_t>();
		//		*(std::uint64_t*)guid2 |= (unsigned __int64)v5 << v3;
		//	}
		//	v3 += 8;
		//	++v2;
		//} while (v3 < 0x40);

		//store_->restore_cursor();
		//return wow::guid{guid};
	}
}
