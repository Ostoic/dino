#pragma once

#include <distant/memory/address.hpp>

namespace dino
{
	using address = distant::address;
	using byte = unsigned char;

	template <class T>
	T reverse_bytes(T x)
	{
		auto* x_ptr = reinterpret_cast<byte*>(&x);
		auto& x_bytes = *reinterpret_cast<std::array<byte, sizeof(T)>*>(x_ptr);

		for (int i = 0; i < sizeof(T) / 2; i++)
			std::swap(x_bytes[i], x_bytes[sizeof(T) - i - 1]);

		return x;
	}

	template <class T>
	std::array<byte, sizeof(T)>& bytes_of(T& x)
	{
		return *reinterpret_cast<std::array<byte, 4>*>(&x);
	}

	template <class T>
	std::array<byte, sizeof(T)> bytes_of(const T& x)
	{
		return *reinterpret_cast<const std::array<byte, 4>*>(&x);
	}

	template <class To>
	To& bind_value(address address)
	{
		return *reinterpret_cast<To*>(static_cast<address::address_type>(address));
	}

	inline address bind_value(address address)
	{
		return bind_value<decltype(address)>(address);
	}

	template <class To>
	To& deref_as(address address)
	{
		return *reinterpret_cast<To*>(static_cast<address::address_type>(address));
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
		return reinterpret_cast<fn_ptr<Fn>>(static_cast<address::address_type>(address));
	}
}
