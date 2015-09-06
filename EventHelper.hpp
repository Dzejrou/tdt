#pragma once

#include <Ogre.h>
#include <cstdlib>
#include "Enums.hpp"
class EntitySystem;

namespace EventHelper
{
	/**
	 * Brief: Sets the type of a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 * Param: The new type.
	 */
	void set_event_type(EntitySystem&, std::size_t, EVENT_TYPE);

	/**
	 * Brief: Returns the type of a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 */
	EVENT_TYPE get_event_type(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the target entity (the subject of the event) of
	 *        a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 * Param: ID of the target.
	 */
	void set_target(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the target entity (the subject of the event) of
	 *        a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 */
	std::size_t get_target(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the radius handlers have to be in in order to be
	 *        able to handle a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 * Param: The new radius.
	 */
	void set_radius(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the radius handlers have to be in in order to be
	 *        able to handle a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 */
	Ogre::Real get_radius(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the activity state of a given event.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 * Param: ID for active, false for inactive.
	 */
	void set_active(EntitySystem&, std::size_t, bool = true);

	/**
	 * Brief: Returns true if a given event is active,
	 *        false otherwise.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the event.
	 */
	bool is_active(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the entity that handles a given event.
	 * Param: Entity system containing both the entity and the event.
	 * Param: ID of the event.
	 * Param: ID of the handling entity.
	 */
	void set_event_handler(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the entity that handles a given event.
	 * Param: Entity system containing both the entity and the event.
	 * Param: ID of the event.
	 */
	std::size_t get_event_handler(EntitySystem&, std::size_t);
}