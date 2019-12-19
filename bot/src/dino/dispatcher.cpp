#include "dispatcher.hpp"
#include "log.hpp"

#include "events/chat_events.hpp"
#include "events/combat_log_events.hpp"
#include "events/console_events.hpp"
#include "events/dino_events.hpp"
#include "events/endscene_events.hpp"
#include "events/glue_events.hpp"
#include "events/net_events.hpp"
#include "events/server_events.hpp"
#include "events/spell_events.hpp"
#include "events/warden_events.hpp"
#include "events/world_events.hpp"

#include <typeinfo>
#include <boost/mp11.hpp>

namespace dino
{
	dispatcher& dispatcher::get()
	{
		static dispatcher s_;
		return s_;
	}

	std::vector<std::string> dispatcher::get_event_list()
	{
		namespace mp11 = boost::mp11;
		using all_events = mp11::mp_set_union<
			events::combat_log_events,
			events::console_events,
			//events::dino_events,
			events::endscene_events,
			events::glue_events,
			events::net_events,
			events::server_events,
			events::spell_events,
			events::warden_events,
			events::world_events
		>;

		log::info("[dev] mp_list size: {}", mp11::mp_size<all_events>::value);
		//unsigned int event_count = 0;

		auto events = std::vector<std::string>{};
		//mp11::mp_for_each<all_events>([]()
		//{
		//	//event_count++;
		//	log::info("[dev] current");
		//	//log::info("[dev] event: {}", typeid(event).name());
		//	//events.push_back(typeid(event).name());
		//});

		log::info("[dev] after event");
		//log::info("[dev] {} events found", event_count);
		return events;
	}

}