#include "core.hpp"

#include "../wow/lua.hpp"

#include <fstream>

namespace dino::script
{
	void load(const std::filesystem::path& path)
	{
		auto file = std::ifstream{path};
		if (!file)
			return;

		std::string script;
		std::string line;
		while (std::getline(file, line))
			script += std::move(line) + "\n";

		wow::lua::run("{}", script);
	}
}