#include "console.hpp"

#include "../session.hpp"
#include "offsets.hpp"

#include <unordered_map>

namespace dino::wow::console
{
	void clear()
	{
		bind_value<unsigned int>(offsets::console::num_lines) = 257;
		bind_fn<void()>(offsets::console::clear_fn)();
	}

	void close()
	{
		dino::bind_value<bool>(offsets::console::active) = false;
	}

	void open()
	{
		dino::bind_value<bool>(offsets::console::active) = true;
	}

	void enable()
	{
		dino::bind_value<bool>(offsets::console::enabled) = true;
	}

	void disable()
	{
		dino::bind_value<bool>(offsets::console::enabled) = false;
	}

	bool is_enabled()
	{
		return dino::bind_value<bool>(offsets::console::enabled);
	}

	bool is_open()
	{
		return dino::bind_value<bool>(offsets::console::active);
	}

	unsigned int num_lines()
	{
		return dino::bind_value<unsigned int>(offsets::console::num_lines);
	}

	unsigned char keybind()
	{
		return dino::bind_value<unsigned char>(offsets::console::keybind);
	}

	void set_keybind(const unsigned char c)
	{
		dino::bind_value<unsigned char>(offsets::console::keybind) = c;
	}

	std::string last_line()
	{
		return std::string{bind_value<char[64]>(offsets::console::last_line)};
	}

	command last_command()
	{
		return command{last_line(), num_lines()};
	}

	//bool register_command(const std::string& name, fn_ptr<command_t> command)
	//{
	//	static std::unordered_map<std::string, fn_ptr<command_t>> commands;
	//	commands[name] = command;

	//	auto register_command = bind_fn<int(const char*, fn_ptr<command_t>, int, int)>(offsets::console::register_fn);

	//	log::info("Command registered: >{}<", reinterpret_cast<void*>(command));
	//	register_command(name.c_str(), command, 5, 0);
	//	return true;
	//}

	void write(const std::string& message)
	{
		auto write = bind_fn<void(const char*, int)>(offsets::console::write_fn);
		write(message.c_str(), 0);
	}

//console::command
	command::command(const std::string& cmd, std::uint32_t line_executed)
		: cmd_{cmd}
		, line_executed_{line_executed}
	{}

	void command::update()
	{
		line_executed_ = num_lines();
		cmd_ = last_line();
	}

	std::uint32_t command::line_number() const noexcept
	{
		return line_executed_;
	}

	bool command::is_new() const
	{
		return line_executed_ == num_lines();
	}

	const std::string& command::cmd() const noexcept
	{
		return cmd_;
	}
}