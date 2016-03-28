#pragma once

#include <string>
#include "Enums.hpp"
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the event handler component.
 */
namespace EventHandlerHelper
{
	/**
	 * Brief: Sets the name of the table that contains event the handler function
	 *        of a given entity.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new handler table name.
	 */
	void set_handler(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * Brief: Returns the name of the table that contains event the handler function
	 *        of a given entity.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_handler(EntitySystem&, tdt::uint);

	/**
	 * Brief: Returns true if a given entity can handle a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the entity.
	 * Param: The type of the event.
	 */
	bool can_handle(EntitySystem&, tdt::uint, EVENT_TYPE);

	/**
	 * Brief: Adds a given event into the list of possible events of a
	 *        given entity.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the entity.
	 * Param: The type of the event.
	 */
	void add_possible_event(EntitySystem&, tdt::uint, EVENT_TYPE);

	/**
	 * Brief: Removes a given event from the list of possible events of a
	 *        given entity.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the entity.
	 * Param: The type of the event.
	 */
	void delete_possible_event(EntitySystem&, tdt::uint, EVENT_TYPE);
}