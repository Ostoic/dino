#include "patch.hpp"

#include "../log.hpp"
#include "../internal/string.hpp"

#include <distant/memory/protect_guard.hpp>

namespace dino::hook
{
	patch::patch(patch&& other)
		: destination_{other.destination_}
		, data_{std::move(other.data_)}
		, original_{std::move(other.original_)}
	{
		other.destination_ = 0;
	}

	patch::patch(address destination, std::vector<byte>&& data)
		: destination_{destination}
		, data_{std::move(data)}
	{}

	patch& patch::operator=(patch&& other)
	{
		destination_ = other.destination_;
		data_ = std::move(other.data_);
		original_ = std::move(other.original_);
		other.destination_ = 0;
		return *this;
	}

	void patch::apply()
	{
		const auto size = data_.size();
		auto guard = distant::make_protect_guard<distant::page_protection::execute_readwrite>(distant::current_process(), destination_, size);
		byte& dest_byte = bind_value<byte>(destination_);
		byte* dest_bytes = &dest_byte;

		log::debug(OBFUSCATE("[packet::apply] destination: {}"), destination_);
		log::debug(OBFUSCATE("[packet::apply] size: {}"), size);
		log::debug(OBFUSCATE("[packet::apply] dest_bytes: {}"), dest_bytes);

		log::debug(OBFUSCATE("[packet::apply] dest_bytes: {}"), internal::format_bytes(dest_bytes, dest_bytes + size));

		// Save original bytes
		std::copy(dest_bytes, dest_bytes + size, std::back_inserter(original_));
		log::debug(OBFUSCATE("[packet::apply] original_: {}"), internal::format_bytes(original_));	

		// Patch new bytes
		std::copy(data_.begin(), data_.end(), dest_bytes);
		log::debug(OBFUSCATE("[packet::apply] dest_bytes: {}"), internal::format_bytes(dest_bytes, dest_bytes + size));
	}

	void patch::restore()
	{
		auto guard = distant::make_protect_guard<distant::page_protection::execute_readwrite>(distant::current_process(), destination_, original_.size());
		byte& dest_byte = bind_value<byte>(destination_);
		byte* dest_bytes = &dest_byte;
		log::debug(OBFUSCATE("[packet::restore] destination: {}"), destination_);

		// Restore original bytes
		std::copy(original_.begin(), original_.end(), dest_bytes);
		log::debug(OBFUSCATE("[packet::restore] dest_bytes: {}"), internal::format_bytes(dest_bytes, dest_bytes + original_.size()));
	}
}