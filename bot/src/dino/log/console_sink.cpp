#include "console_sink.hpp"
#include "../wow/console.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <unordered_map>

namespace dino::log
{
	std::shared_ptr<spdlog::logger>& file_logger(const std::string& name)
	{
		static auto loggers = std::unordered_map{
			std::pair{name,  spdlog::basic_logger_mt(name, fmt::format("logs/{}", name))}
		};

		if (loggers.count(name) == 0)
			loggers[name] = spdlog::basic_logger_mt(name, fmt::format("logs/{}", name));

		return loggers[name];
	}

	std::shared_ptr<spdlog::logger>& console_logger()
	{
		static auto console_logger_ = [&] {
			auto console_sink = std::make_shared<console_sink_st>();
			return std::make_shared<spdlog::logger>("console", std::move(console_sink));
		}();

		return console_logger_;
	}
}