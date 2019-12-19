#pragma once

#include "offsets.hpp"

namespace dino::wow
{
	class cvar
	{
	public:
		static cvar lookup(std::string name);

	public:
		const std::string& name() const noexcept;

		std::string value() const;
		std::string default_value() const;

		unsigned int data() const;
		bool reset() const;

		address base() const noexcept;

		bool valid() const noexcept;

	private:
		explicit cvar(address base, std::string&& name);
		cvar() = default;

	private:
		address base_;
		std::string name_;
	};
}