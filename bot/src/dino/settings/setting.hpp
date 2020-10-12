#pragma once

#include "../events/dino_events.hpp"

namespace dino::settings
{
	// Idea setting class:
	// fn call operator(): so that we access settings through global inline function objects
	//		keeps the same interface while making setting creation simpler.
	// default_value: for use with internal::settings::initialize.

	// Also consider making it so that we can make new settings at runtime, etc (virtual)

	template <class Event, class T>
	class setting
	{
	public:
		explicit setting(T&& value, Event&& event);
		setting() = default;

	public:
		const T& operator()() const noexcept;

		void set(T&& value);

	private:
		T value_;
	};

	//template <class T, class Event>
	//explicit setting<T, Event>::setting(T&& value) -> setting<T, Event>;

	//template<class Event, class T>
	//setting(const T& value, ) -> setting<Event, T>;
}

#include "../scheduler.hpp"

namespace dino::settings
{
	template <class Event, class T>
	setting<Event, T>::setting(T&& value, Event&& event)
		: value_{std::forward<T>(value)}
	{}

	template <class Event, class T>
	const T& setting<Event, T>
		::operator ()() const noexcept
	{
		return value_;
	}

	template <class Event, class T>
	void setting<Event, T>
		::set(T&& value)
	{
		const T old = value;
		value_ = std::forward<T>(value);
		scheduler::enqueue(Event{old});
	}
}