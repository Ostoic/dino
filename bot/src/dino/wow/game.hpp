#pragma once

#include <distant/process.hpp>

#include "object_manager.hpp"

namespace dino::wow
{
	class game
	{
	public:
		game() = default;

		wow::object_manager& object_manager() noexcept;
		const wow::object_manager& object_manager() const noexcept;

	private:
		distant::process process_;
	};
}
