#pragma once

#include <string>
#include <functional>
#include <spdlog/spdlog.h>

#include "offsets.hpp"

namespace dino::wow::console
{
	using command_t = int(const char*, const char*);

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
	bool register_command(const std::string& name, fn_ptr<command_t> command);

	template <class... Args>
	void write(const std::string& format, Args&&... args)
	{
		if (console::num_lines() >= 256)
			console::clear();

		auto write = bind_fn<void(const char*, int)>(offsets::console::write_fn);
		write(fmt::format(format, std::forward<Args>(args)...).c_str(), 0);
	}

	template <class... Args>
	void dino(const std::string& format, Args&&... args)
	{
		return write(fmt::format("[dino] {}", format), std::forward<Args>(args)...);
	}
}