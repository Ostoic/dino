#pragma once

#include "../offset.hpp"

#include <unordered_map>

namespace dino::hook
{
	class vmt_hook
	{
	public:
		explicit vmt_hook(address vtable);
		explicit vmt_hook(address vtable, std::size_t index, address new_method);
		explicit vmt_hook(vmt_hook&& other);

		~vmt_hook();

	public:
		void hook(std::size_t index, address new_method);
		void unhook(std::size_t index);

		bool is_hooked(std::size_t index) const;

		address operator[](const std::size_t index) const;

	private:
		address vtable_;
		std::unordered_map<std::size_t, address> hooks_;
	};
}

