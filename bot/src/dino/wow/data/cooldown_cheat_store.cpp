#include "cooldown_cheat_store.hpp"

namespace dino::wow::data
{
	cooldown_cheat_store::cooldown_cheat_store(address store_base)
		: cooldown_cheat_store{data::store{store_base}}
	{}

	cooldown_cheat_store::cooldown_cheat_store(data::store store)
		: store_{store}
	{
		store_->restore_cursor();
	}

	cooldown_cheat_store* cooldown_cheat_store::operator->() noexcept
	{
		return this;
	}

	const cooldown_cheat_store* cooldown_cheat_store::operator->() const noexcept
	{
		return this;
	}

	void cooldown_cheat_store::set_receiver(const guid receiver)
	{
		store_->put(static_cast<std::uint64_t>(receiver));
		store_->restore_cursor();
	}

	guid cooldown_cheat_store::receiver() const
	{
		const auto result = store_->pull<wow::guid>();
		store_->restore_cursor();
		return guid{result};
	}

	void cooldown_cheat_store::seek_end()
	{
		store_->restore_cursor();
		const auto initial = store_->cursor();

		store_->seek(initial + sizeof(std::uint64_t));
	}
}