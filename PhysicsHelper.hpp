#pragma once

#include <Ogre.h>
#include <cstdlib>
#include <numeric>
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
	 * Note: The difference with move_to is that this function does not set
	 *       the position of the scene node this entity is attached to
	 *       and thus does not move the entity's model as well.
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
	void set_half_height(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the half height of a given entity (which is used to
	 *        balance the fact that some models do not have their center
	 *        on the level of their feet).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_half_height(EntitySystem&, std::size_t);

	/**
	 * Brief: Moves a given entity to a given point in space (absolute movement).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Target coordinate.
	 * Note: The difference with set_position is that this function also sets
	 *       the position of the scene node this entity is attached to (if
	 *       such node exists) and thus moves the entity's model as well.
	 */
	void move_to(EntitySystem&, std::size_t, Ogre::Vector3);

	/**
	 * Brief: Returns the distance between two given entities.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the first entity.
	 * Param: ID of the second entity.
	 */
	Ogre::Real get_distance(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the size of the angle bewteen two given vectors as Ogre::Real
	 *        which can then be used in Ogre::Radian constructor for conversion to Radians.
	 *        (The reason for this is that Lua does not have the notion of radians and as such
	 *        using floating point numbers is easier.)
	 * Param: Vector #1.
	 * Param: Vector #2.
	 */
	Ogre::Real get_angle(Ogre::Vector3, Ogre::Vector3);

	/**
	 * Brief: Sets the position of a given entity disregarding it's Y coordinate.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new position (vector2 containing the x and z coordinates.)
	 */
	void set_2d_position(EntitySystem&, std::size_t, Ogre::Vector2);

	/**
	 * Brief: Returns the X and Z coordinates of a given entity's position.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Note: Cannot use const reference like in the usual get_position function
	 *       because this method creates a proxy Vector2 which cannot be passed
	 *       as an lvalue reference due to it being a temporary object.
	 */
	Ogre::Vector2 get_2d_position(EntitySystem&, std::size_t);
}