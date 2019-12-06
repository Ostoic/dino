#pragma once

#include <string>
#include <filesystem>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "../session.hpp"

namespace dino::wow::lua
{
	void execute(const std::string& script);

	template <class... Args>
	void run(const std::string& format, Args&&... args)
	{
		auto script = fmt::format(format, std::forward<Args>(args)...);
		session::queue_task([script = std::move(script)] {
			lua::execute(script);
		});
	}

	bool load_file(const std::filesystem::path& path);
	std::string get_text(const std::string& variable_name);

	class action
	{
	public:
		action()
			: name_{get_text("dino_action")}
			, data_{get_text("dino_action_data")}
		{
			if (this->is_valid())
				lua::run("dino_action = nil dino_action_data = nil");
		}

		const std::string& name() const noexcept
		{
			return name_;
		}

		const std::string& data() const noexcept
		{
			return data_;
		}

		bool is_valid() const noexcept
		{
			return !name_.empty();
		}

	private:
		std::string name_;
		std::string data_;
	};

	inline action last_action()
	{
		return action{};
	}

	/*
	const auto action = wow::lua::get_text("dino_action");
	if (action == "lua.execute")
	{
		wow::lua::run(
			"dino_action = nil dino_action_data = nil {}",
			wow::lua::get_text("dino_action_data")
		);
	}
	else if (action == "event.emit")
	{
		const auto data = wow::lua::get_text("dino_action_data");
		wow::chat::dino("action_data: {}", data);
		wow::lua::run("dino_action = nil dino_action_data = nil");
	}
	*/

	std::string random_variable(std::size_t length);

	template <class... Args>
	std::string result_of(Args&&... args)
	{
		const auto var = random_variable(10);
		lua::run("{} = {}", var, fmt::format(std::forward<Args>(args)...));

		const auto result = get_text(var);
		lua::run("{} = nil", var);
		return result;
	}
}
