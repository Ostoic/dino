#include "rc4.hpp"
#include "byte_ops.hpp"
#include "../../config.hpp"

#include <boost/assert.hpp>

namespace dino::wow::warden::rc4
{
	std::vector<byte> decrypt(const std::vector<byte>& data, const std::vector<byte>& outgoing_key)
	{
		return encrypt(data, outgoing_key);
	}

	std::vector<byte> encrypt(const std::vector<byte>& data, const std::vector<byte>& outgoing_key)
	{
		auto key = outgoing_key;
		auto result = data;
		BOOST_ASSERT(key.size() >= 0x101);
		for (unsigned int i = 0; i < result.size(); i++)
		{
			key[0x100]++;
			key[0x101] += key[key[0x100] & 0x0FF];

			const auto temp = key[key[0x101] & 0x0FF];
			key[key[0x101] & 0x0FF] = key[key[0x100] & 0x0FF];
			key[key[0x100] & 0x0FF] = temp;

			result[i] = (result[i] ^ key[(key[key[0x101] & 0x0FF] + key[key[0x100] & 0x0FF]) & 0x0FF]);
		}

		return result;
	}
}