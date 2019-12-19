#pragma once

#include <string>
#include <spdlog/spdlog.h>

#include "console_sink.hpp"

#include <obfuscator.hpp>

namespace dino::log
{
	template <class String, class... Args>
	void critical(const String& format, Args&&... args)
	{
		log::file_logger(OBFUSCATE("dino.log"))->critical(format, std::forward<Args>(args)...);
		log::console_logger()->critical(format, std::forward<Args>(args)...);
		log::file_logger(OBFUSCATE("dino.log"))->flush();
	}

	template <class String, class... Args>
	void error(const String& format, Args&&... args)
	{
		log::file_logger(OBFUSCATE("dino.log"))->error(format, std::forward<Args>(args)...);
		log::console_logger()->error(format, std::forward<Args>(args)...);
		log::file_logger(OBFUSCATE("dino.log"))->flush();
	}

	template <class String, class... Args>
	void info(const String& format, Args&&... args)
	{
		log::file_logger(OBFUSCATE("dino.log"))->info(format, std::forward<Args>(args)...);
		log::console_logger()->info(format, std::forward<Args>(args)...);
		log::file_logger(OBFUSCATE("dino.log"))->flush();
	}

	template <class String, class... Args>
	void debug(const String& format, Args&&... args)
	{
		log::file_logger(OBFUSCATE("dino.log"))->debug(format, std::forward<Args>(args)...);
		log::console_logger()->debug(format, std::forward<Args>(args)...);
		log::file_logger(OBFUSCATE("dino.log"))->flush();
	}
}
