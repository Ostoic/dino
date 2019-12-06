#pragma once

#include "../settings.hpp"

#include <nlohmann/json_fwd.hpp>

namespace dino::script::settings
{
	using json = nlohmann::json;

	void modify(const json& params);
}