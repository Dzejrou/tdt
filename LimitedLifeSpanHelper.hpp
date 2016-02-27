#pragma once

#include <Ogre.h>
#include <cstdlib>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the limited life span component.
 */
namespace LimitedLifeSpanHelper
{
	/**
	 * Brief: Sets the life span of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new life span.
	 */
	void set_max_time(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the life span of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_max_time(EntitySystem&, std::size_t);

	/**
	 *
	 * Brief: Returns the life time of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_curr_time(EntitySystem&, std::size_t);

	/**
	 * Brief: Advances the life time of a given entity by a given value.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The value to advance by.
	 */
	void advance_curr_time(EntitySystem&, std::size_t, Ogre::Real);
}