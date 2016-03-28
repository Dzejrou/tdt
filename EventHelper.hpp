#pragma once

#include "Enums.hpp"
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the event component.
 */
namespace EventHelper
{
	/**
	 * Brief: Sets the type of a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 * Param: The new type.
	 */
	void set_event_type(EntitySystem&, tdt::uint, EVENT_TYPE);

	/**
	 * Brief: Returns the type of a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 */
	EVENT_TYPE get_event_type(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the target entity (the subject of the event) of
	 *        a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 * Param: ID of the target.
	 */
	void set_target(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the target entity (the subject of the event) of
	 *        a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 */
	tdt::uint get_target(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the radius handlers have to be in in order to be
	 *        able to handle a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 * Param: The new radius.
	 */
	void set_radius(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the radius handlers have to be in in order to be
	 *        able to handle a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 */
	tdt::real get_radius(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the activity state of a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 * Param: ID for active, false for inactive.
	 */
	void set_active(EntitySystem&, tdt::uint, bool = true);

	/**
	 * Brief: Returns true if a given event is active,
	 *        false otherwise.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 */
	bool is_active(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the entity that handles a given event.
	 * Param: Entity system containing both the entity and the event.
	 * Param: ID of the event.
	 * Param: ID of the handling entity.
	 */
	void set_event_handler(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the entity that handles a given event.
	 * Param: Entity system containing both the entity and the event.
	 * Param: ID of the event.
	 */
	tdt::uint get_event_handler(EntitySystem&, tdt::uint);
}