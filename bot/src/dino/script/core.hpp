#pragma once

#include <string_view>
#include <filesystem>

namespace dino::script
{
	void load(const std::filesystem::path& path);

	constexpr std::string_view emitter_script =
		#include "emitter.lua"

	constexpr std::string_view json_script =
		#include "json.lua"
}