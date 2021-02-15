#pragma once

#include <vector>
#include "../../offset.hpp"

namespace dino::wow::warden::rc4
{
	std::vector<byte> encrypt(const std::vector<byte>& data, const std::vector<byte>& outgoing_key);
	std::vector<byte> decrypt(const std::vector<byte>& data, const std::vector<byte>& outgoing_key);
}