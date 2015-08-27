#pragma once

#include <string>
#include "Enums.hpp"
class EntitySystem;

namespace EventHandlerHelper
{
	void set_handler(EntitySystem&, std::size_t, const std::string&);

	const std::string& get_handler(EntitySystem&, std::size_t);

	bool can_handle(EntitySystem&, std::size_t, EVENT_TYPE);

	void add_possible_event(EntitySystem&, std::size_t, EVENT_TYPE);

	void delete_possible_event(EntitySystem&, std::size_t, EVENT_TYPE);
}