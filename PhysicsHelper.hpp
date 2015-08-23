#pragma once

#include <Ogre.h>
class PhysicsComponent;
class EntitySystem;

namespace PhysicsHelper
{
	/**
	 * Brief: Changes the solid state of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: True for solid, false for non-solid.
	 */
	void set_solid(EntitySystem&, std::size_t, bool);

	/**
	 * Brief: Returns true if a given entity is solid, false otherwise.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	bool is_solid(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the position of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: The new position.
	 */
	void set_position(EntitySystem&, std::size_t, const Ogre::Vector3&);

	/**
	 * Brief: Returns the position of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Parma: ID of the entity.
	 */
	const Ogre::Vector3& get_position(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the half height of a given entity (which is used to
	 *        balance the fact that some models do not have their center
	 *        on the level of their feet).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: The new half height value.
	 */
	void set_halfheight(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the half height of a given entity (which is used to
	 *        balance the fact that some models do not have their center
	 *        on the level of their feet).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_halfheight(EntitySystem&, std::size_t);
}