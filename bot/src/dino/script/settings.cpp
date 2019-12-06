#include "settings.hpp"

#include <nlohmann/json.hpp>

namespace dino::script::settings
{
	void modify(const json& params)
	{
		const auto setting = params["setting"];
		const auto arg1 = params["arg1"];

		//if (!setting.is_string())

		//dino::settings::modify<dino::settings::fps>(arg1.get());
	}
}
