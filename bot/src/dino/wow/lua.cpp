#include "lua.hpp"

#include "../session.hpp"
#include "../wow/console.hpp"

#include <random>
#include <fstream>

namespace dino::wow::lua
{
	namespace
	{
		void framescript_execute(const std::string& script)
		{
			const auto execute = bind_fn<int(const char*, const char*, int)>(
				offsets::lua::framescript_execute_fn
			);

			execute(script.c_str(), script.c_str(), 0);
		}
	}

	void execute(const std::string& script)
	{
		framescript_execute(script);
	}

	bool load_file(const std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
			return false;

		auto file = std::ifstream{path};
		std::string script;
		script.reserve(1024);

		std::string input;
		while (std::getline(file, input))
			script += std::move(input) + '\n';

		lua::run("{}", script);
		return true;
	}

	std::string random_variable(const std::size_t length)
	{
		constexpr int x = 'Z';
		std::random_device r;
		auto gen = std::default_random_engine{r()};
		auto unif = std::uniform_int_distribution<unsigned int>{
			static_cast<unsigned int>('A'),
			static_cast<unsigned int>('Z')
		};

		std::string result;
		std::generate_n(
			std::back_inserter(result),
			length,
			[&] { return unif(gen); }
		);

		return result;
	}

	std::string get_text(const std::string& variable_name)
	{
		const auto get = bind_fn<const char*(const char*, int, int)>(
			offsets::lua::framescript_get_text_fn
		);

		return get(variable_name.c_str(), -1, 0);
	}
}