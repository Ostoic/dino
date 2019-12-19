#pragma once

#include "../offsets.hpp"

namespace dino::wow::db
{
	class db
	{
	public:
		explicit db(address object_base);

	public:
		bool is_loaded() const;

		unsigned int max_index() const;
		unsigned int min_index() const;
		unsigned int num_rows() const;

		const char** string_table() const;
		const void** functon_table() const;
		const void* first_row() const;
		const void* rows() const;

		char** string_table();
		void** functon_table();
		void* first_row();
		void* rows();

	private:
		mutable address object_base_;
	};

	//void* vtable;
	//int is_loaded;
	//int num_rows;
	//int max_index;
	//int min_index;
	//char** string_table;
	//void* funcTable2;
	//int* first_row;
	//int* rows;
}