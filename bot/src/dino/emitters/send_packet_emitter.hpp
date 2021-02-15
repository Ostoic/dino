#pragma once

#include <array>

#include "../hook/patch.hpp"

namespace dino::emitters
{
	class send_packet_emitter
	{
	public:
		send_packet_emitter() = default;
		static void install();
		static void uninstall();

		static send_packet_emitter& get() noexcept;

	private:
		std::vector<hook::patch> patches_;
	};
}