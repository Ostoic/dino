#include "send_packet_emitter.hpp"

#include "../wow/offsets.hpp"
#include "../wow/world/world.hpp"
#include "../log.hpp"
#include "../internal/string.hpp"

namespace dino::emitters
{
	send_packet_emitter& send_packet_emitter::get() noexcept
	{
		static auto emitter_ = send_packet_emitter{};
		return emitter_;
	}

	void send_packet_emitter::install()
	{
		auto& patches = send_packet_emitter::get().patches_;
		const auto target = &wow::world::client_services::prehook_send_packet;
		const auto target_address = address{reinterpret_cast<void* const&>(target)};

		const auto install_patch = [&](const address base) {
			const auto diff_bytes = bytes_of(static_cast<address::address_type>(target_address - base - 5));
			patches.push_back(hook::patch{base + 1, diff_bytes});
			patches.back().apply();
		};

		install_patch(wow::offsets::net::client_services::send_packet_invocation1);
		install_patch(wow::offsets::net::client_services::send_packet_invocation2);
		install_patch(wow::offsets::net::client_services::send_packet_invocation3);
		install_patch(wow::offsets::net::client_services::send_packet_invocation4);
		install_patch(wow::offsets::net::client_services::send_packet_invocation5);
		log::info(OBFUSCATE("[send_packet_emitter::install] installed"));
		log::info(OBFUSCATE("[send_packet_emitter::install] prehook_send_packet: {}"), target_address);
	}

	void send_packet_emitter::uninstall()
	{
		auto& patches = send_packet_emitter::get().patches_;
		patches.clear();
		log::info(OBFUSCATE("[send_packet_emitter::uninstall] uninstalled"));
	}
}