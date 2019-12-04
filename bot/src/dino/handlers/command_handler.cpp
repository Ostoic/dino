#include "command_handler.hpp"
#include "../version.hpp"
#include "../session.hpp"
#include "../wow/lua.hpp"

#include <unordered_set>

namespace dino::handlers
{
	command_handler& command_handler::get() noexcept
	{
		static command_handler singleton;
		return singleton;
	}
}