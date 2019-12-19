#include "vmt_hook.hpp"
#include "../log.hpp"

namespace dino::hook
{
	vmt_hook::vmt_hook(const address vtable)
		: vtable_{vtable}
	{}

	vmt_hook::vmt_hook(const address vtable, const std::size_t index, const address new_method)
		: vmt_hook{vtable}
	{
		this->hook(index, new_method);
	}

	vmt_hook::vmt_hook(vmt_hook&& other)
		: vtable_{other.vtable_}
		, hooks_{std::move(other.hooks_)}
	{}

	vmt_hook::~vmt_hook()
	{
		//for (const auto [key, value] : hooks_)
			//this->unhook(key);
	}

	address vmt_hook::operator[](const std::size_t index) const
	{
		return vtable_ + sizeof(void*) * index;
	}

	void vmt_hook::hook(const std::size_t index, const address new_method)
	{
		auto& me = *this;
		auto& fn_ptr = deref_as<address>(me[index]);

		// save old ptr
		if (!hooks_.contains(index))
			hooks_[index] = fn_ptr;

		DWORD original, buffer;
		VirtualProtect(&fn_ptr, sizeof(address), PAGE_EXECUTE_READWRITE, &original);
		fn_ptr = new_method;
		VirtualProtect(&fn_ptr, sizeof(address), original, &buffer);
	}

	void vmt_hook::unhook(const std::size_t index)
	{
		this->hook(index, hooks_[index]);
		hooks_.erase(index);
	}

	bool vmt_hook::is_hooked(const std::size_t index) const
	{
		return hooks_.contains(index);
	}
}

