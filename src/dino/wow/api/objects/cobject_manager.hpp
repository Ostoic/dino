#pragma once

namespace dino::wow::api::object
{
	class cobject_manager
	{
	public:
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		const_iterator cbegin() const;
		const_iterator cend() const;

	private:
	};
}
