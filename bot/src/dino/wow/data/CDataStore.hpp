#pragma once

#include <cstddef>

#include "../guid.hpp"

namespace dino::wow::data
{
	struct CDataStore_vTable
	{
		void InternalInitialize(unsigned __int8* data, unsigned int base, unsigned int alloc);
		void InternalDestroy(unsigned __int8* data, unsigned int base, unsigned int alloc);
		int InternalFetchRead(unsigned int pos, unsigned int bytes, unsigned __int8* data, unsigned int base, unsigned int alloc);
		int InternalFetchWrite(void* self, unsigned int pos, unsigned int bytes, unsigned __int8* data, unsigned int base, unsigned int alloc);
		void Destructor(void* self);
		void Reset(void* self);
		int IsRead(void* self);
		void Finalize(void* self);
		void GetBufferParams(void* self, const void** data, unsigned int* size, unsigned int* alloc);
		void DetachBuffer(void* self, void** buffer, unsigned int* size, unsigned int* alloc);
	};

	class CDataStore
	{
	public:
		CDataStore_vTable* vTable;
		unsigned __int8* m_buffer;
		unsigned int m_base;
		unsigned int m_alloc;
		unsigned int m_size;
		unsigned int m_cursor;

	public:
		void GetPackedGUID(wow::guid* guid);
		void GetString(char* out, unsigned int max_length);
		void GetStringPtr(char** out, unsigned int max_length);

		void GetFloat(float* out);
		void GetInt8(std::int8_t* out);
		void GetInt16(std::int16_t* out);
		void GetInt32(std::int32_t* out);
		void GetInt64(std::int64_t* out);
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