#pragma once

#include <distant/memory/address.hpp>

namespace dino
{
	using address = distant::address;
	using byte = unsigned char;

	template <class To>
	To& bind_value(address address)
	{
		return *reinterpret_cast<To*>(static_cast<unsigned int>(address));
	}

	inline address bind_value(address address)
	{
		return bind_value<decltype(address)>(address);
	}

	template <class To>
	To& deref_as(address address)
	{
		return *reinterpret_cast<To*>(static_cast<unsigned int>(address));
	}

	inline address deref_as(address address)
	{
		return deref_as<decltype(address)>(address);
	}

	template <class T>
	struct function;

	template <class R, class... Ts>
	struct function<R(Ts...)>
	{
		using type = R(*)(Ts...);
	};

	template <class T>
	using fn_ptr = typename function<T>::type;

	//template <class Fn>

	template <class Fn>
	fn_ptr<Fn> bind_fn(address address)
	{
		return reinterpret_cast<fn_ptr<Fn>>(static_cast<unsigned int>(address));
	}
}
