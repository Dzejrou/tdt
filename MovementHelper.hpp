#pragma once

#include <Ogre.h>
class EntitySystem;

namespace MovementHelper
{
	/**
	 * Brief: Returns the speed modifier of a given entity.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_speed_modifier(EntitySystem&, std::size_t);

	/**
	 * Brief: Changes the speed modifier of a given entity to a given value.
	 * Param: ID of the entity.
	 * Param: New speed value.
	 */
	void set_speed_modifier(EntitySystem&, std::size_t, Ogre::Real);
}