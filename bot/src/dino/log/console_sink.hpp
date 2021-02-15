#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>

#include <mutex>

#include "../wow/console.hpp"

namespace dino::log
{
	template <class Mutex>
	class console_sink : public spdlog::sinks::base_sink<Mutex>
	{
	public:
	protected:
		void console_sink::sink_it_(const spdlog::details::log_msg& msg)
		{
			spdlog::memory_buf_t formatted;
			spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);

			auto color = wow::console::color::standard;
			switch (msg.level)
			{
			case spdlog::level::level_enum::info:
				color = wow::console::color::standard;
				break;

			case spdlog::level::level_enum::err:
				color = wow::console::color::error;
				break;

			case spdlog::level::level_enum::critical:
				color = wow::console::color::error;
				break;


			case spdlog::level::level_enum::warn:
				color = wow::console::color::warning;
				break;

			case spdlog::level::level_enum::off:
				color = wow::console::color::echo;
				break;
			}
			wow::console::write(fmt::to_string(formatted), color);
		}

		void console_sink::flush_()
		{
		}
	};

	using console_sink_mt = console_sink<std::mutex>;
	using console_sink_st = console_sink<spdlog::details::null_mutex>;

	std::shared_ptr<spdlog::logger>& file_logger(const std::string& name);
	std::shared_ptr<spdlog::logger>& console_logger();
}