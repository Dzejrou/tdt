#pragma once

#include <Ogre.h>
#include <cstdlib>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the movement component.
 */
namespace MovementHelper
{
	/**
	 * Brief: Returns the speed modifier of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_speed_modifier(EntitySystem&, std::size_t);

	/**
	 * Brief: Changes the speed modifier of a given entity to a given value.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: New speed value.
	 */
	void set_speed_modifier(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the direction from a given entity to another given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the first entity.
	 * Param: ID of the second entity.
	 */
	Ogre::Vector3 dir_to(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the direction a given entity is facing.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Vector3 get_dir(EntitySystem&, std::size_t);

	/**
	 * Brief: Returns the opposite direction to the direction a given entity is facing.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Vector3 get_dir_back(EntitySystem&, std::size_t);

	/**
	 * Brief: Returns the direction perpendicular to the direction a given entity is facing.
	 *        (To the left.)
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Vector3 get_dir_left(EntitySystem&, std::size_t);

	/**
	 * Brief: Returns the direction perpendicular to the direction a given entity is facing.
	 *        (To the right.)
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Vector3 get_dir_right(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the original value of a given entity's speed.
	 *        (Used for serialization.)
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	void set_original_speed(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the original speed of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_original_speed(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the speed of a given entity to it's original value.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	void reset_speed(EntitySystem&, std::size_t);
}