#include "cvar.hpp"
#include "../log.hpp"

#include <obfuscator.hpp>

namespace dino::wow
{
	cvar cvar::lookup(std::string name)
	{
		const auto& lookup = deref_as<void*(const char*)>(offsets::cvar::lookup_fn);
		const auto* base = lookup(name.c_str());
		return cvar{base, std::move(name)};
	}

	cvar::cvar(const address base, std::string&& name)
		: base_{base}
		, name_{std::move(name)}
	{}

	std::string cvar::value() const
	{
		return deref_as<const char*>(base_ + offsets::cvar::value_offset);
	}

	std::string cvar::default_value() const
	{
		return deref_as<const char*>(base_ + offsets::cvar::default_value_offset);
	}

	unsigned int cvar::data() const
	{
		return deref_as<unsigned int>(base_ + offsets::cvar::data_offset);
	}

	bool cvar::reset() const
	{
		return deref_as<bool>(base_ + offsets::cvar::reset_offset);
	}

	const std::string& cvar::name() const noexcept
	{
		return name_;
	}

	address cvar::base() const noexcept
	{
		return base_;
	}

	bool cvar::valid() const noexcept
	{
		return base_ != 0;
	}
}