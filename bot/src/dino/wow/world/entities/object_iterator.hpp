#pragma once

#include <boost/iterator/iterator_facade.hpp>

#include <optional>

#include "object_manager.hpp"
#include "../../address.hpp"

namespace dino::wow::objects
{
	template <class Object>
	class object_iterator
		: public boost::iterator_facade<
			object_iterator<Object>,
			Object,
			std::forward_iterator_tag,
			Object&
		>
	{
	public:
		using mgr_t = std::conditional_t<std::is_const_v<Object>, const object_manager, object_manager>;
		using mgr_ref = mgr_t&;
		using mgr_ptr = mgr_t*;

	public:
		constexpr object_iterator() = default;

		constexpr explicit object_iterator(mgr_ref mgr, address address = 0)
			: mgr_{std::addressof(mgr)}
			, address_{address}
		{}

	private:
		friend class boost::iterator_core_access;

		template <class OtherObject>
		constexpr bool equal(const object_iterator<OtherObject>& other) const
		{
			return mgr_ == other.mgr_ && address_ == other.address_;
		}

		void increment()
		{
			m_node = m_node->next();
		}

		Object& dereference() const
		{
			return *reinterpret_cast<Object*>(static_cast<int>(address_));
		}

	private:
		struct enabler {};

	private:
		mgr_ptr mgr_;
		address address_;
	};
}
