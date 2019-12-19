#include "db.hpp"

namespace dino::wow::db
{
	db::db(const address object_base)
		: object_base_{object_base}
	{}

	bool db::is_loaded() const
	{
		return deref_as<const bool>(object_base_ + 0x4);
	}

	unsigned int db::max_index() const
	{
		return deref_as<const unsigned int>(object_base_ + 0xC);
	}

	unsigned int db::min_index() const
	{
		return deref_as<const unsigned int>(object_base_ + 0x10);
	}

	unsigned int db::num_rows() const
	{
		return deref_as<const unsigned int>(object_base_ + 0x8);
	}

	const char** db::string_table() const
	{
		return deref_as<const char**>(object_base_ + 0x14);
	}

	const void** db::functon_table() const
	{
		return deref_as<const void**>(object_base_ + 0x18);
	}

	const void* db::first_row() const
	{
		return deref_as<const void*>(object_base_ + 0x1C);
	}

	const void* db::rows() const
	{
		return deref_as<const void*>(object_base_ + 0x20);
	}

	char** db::string_table()
	{
		return deref_as<char**>(object_base_ + 0x14);
	}

	void** db::functon_table()
	{
		return deref_as<void**>(object_base_ + 0x18);
	}

	void* db::first_row()
	{
		return deref_as<void**>(object_base_ + 0x1C);
	}

	void* db::rows()
	{
		return deref_as<void*>(object_base_ + 0x20);
	}
}