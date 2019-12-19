#pragma once

#include <string>
#include <functional>
#include <spdlog/spdlog.h>

#include "offsets.hpp"

namespace dino::wow::console
{
	using command_t = int(const char*, const char*);

	enum class color
	{
		standard = 0,
		input = 1,
		echo = 2,
		error = 3,
		warning = 4,
		global = 5,
		admin = 6,
		highlight = 7,
		background = 8,
	};

	void clear();
	void close();
	void open();
	void disable();
	void enable();

	bool is_open();
	bool is_enabled();

	unsigned int num_lines();

	unsigned char keybind();
	void set_keybind(unsigned char);

	std::string last_line();

	class command
	{
	public:
		command() = default;
		command(const std::string& cmd, std::uint32_t line_executed);

		std::uint32_t line_number() const noexcept;

		const std::string& cmd() const noexcept;

		bool is_new() const;

		void update();

	private:
		std::string cmd_;
		std::uint32_t line_executed_;
	};

	command last_command();

	// Todo: Doesn't work
	//bool register_command(const std::string& name, fn_ptr<command_t> command);

	template <class... Args>
	void write(const std::string& format, const color color = color::standard, Args&&... args)
	{
		if (console::num_lines() >= 256)
			console::clear();

		auto write = bind_fn<void(const char*, console::color)>(offsets::console::write_fn);
		write(fmt::format(format, std::forward<Args>(args)...).c_str(), color);
	}

	template <class... Args>
	void dino(const std::string& format, Args&&... args)
	{
		return console::write(fmt::format("[dino] {}", format), std::forward<Args>(args)...);
	}
}