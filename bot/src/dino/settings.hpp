#pragma once

#include <any>
#include <string_view>
#include <unordered_map>

#include "scheduler.hpp"
#include "events/dino_events.hpp"

namespace dino
{
	class settings
	{
	public:
		explicit settings() = default;

		template <class T>
		void set(const std::string_view name, T&& value)
		{
			settings_[name] = std::forward<T>(value);
			scheduler::trigger(events::setting_changed{name, settings_[name]});
		}

		void remove(const std::string_view name)
		{
			settings_.erase(name);
		}

		bool contains(const std::string_view name) const noexcept
		{
			return settings_.contains(name);
		}

		template <class T>
		T lookup(const std::string_view name) const noexcept
		{
			return std::any_cast<T>(settings_.at(name));
		}

	private:
		std::unordered_map<std::string_view, std::any> settings_;
	};
}
