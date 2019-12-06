#pragma once

#include <string>
#include <spdlog/spdlog.h>

#include "console_sink.hpp"

namespace dino::log
{
	template <class... Args>
	void critical(Args&&... args)
	{
		log::file_logger("dino.log")->critical(std::forward<Args>(args)...);
		log::console_logger()->critical(std::forward<Args>(args)...);
		log::file_logger("dino.log")->flush();
	}

	template <class... Args>
	void error(Args&&... args)
	{
		log::file_logger("dino.log")->error(std::forward<Args>(args)...);
		log::console_logger()->error(std::forward<Args>(args)...);
		log::file_logger("dino.log")->flush();
	}

	template <class... Args>
	void info(Args&&... args)
	{
		log::file_logger("dino.log")->info(std::forward<Args>(args)...);
		log::console_logger()->info(std::forward<Args>(args)...);
		log::file_logger("dino.log")->flush();
	}

	template <class... Args>
	void debug(Args&&... args)
	{
		log::file_logger("dino.log")->debug(std::forward<Args>(args)...);
		log::console_logger()->debug(std::forward<Args>(args)...);
		log::file_logger("dino.log")->flush();
	}
}
