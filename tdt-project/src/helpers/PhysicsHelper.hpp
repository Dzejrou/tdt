#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the physics component.
 */
namespace PhysicsHelper
{
	/**
	 * \brief Changes the solid state of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param True for solid, false for non-solid.
	 */
	void set_solid(EntitySystem&, tdt::uint, bool);

	/**
	 * \brief Returns true if a given entity is solid, false otherwise.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	bool is_solid(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the position of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param The new position.
	 * \note The difference with move_to is that this function does not set
	 *       the position of the scene node this entity is attached to
	 *       and thus does not move the entity's model as well.
	 */
	void set_position(EntitySystem&, tdt::uint, const Ogre::Vector3&);

	/**
	 * \brief Returns the position of a given entity.
	 * \param Reference to the entity system containing components.
	 * Parma: ID of the entity.
	 */
	const Ogre::Vector3& get_position(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the half height of a given entity (which is used to
	 *        balance the fact that some models do not have their center
	 *        on the level of their feet).
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param The new half height value.
	 */
	void set_half_height(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the half height of a given entity (which is used to
	 *        balance the fact that some models do not have their center
	 *        on the level of their feet).
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	tdt::real get_half_height(EntitySystem&, tdt::uint);

	/**
	 * \brief Moves a given entity to a given point in space (absolute movement).
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param Target coordinate.
	 * \note The difference with set_position is that this function also sets
	 *       the position of the scene node this entity is attached to (if
	 *       such node exists) and thus moves the entity's model as well.
	 */
	void move_to(EntitySystem&, tdt::uint, Ogre::Vector3);

	/**
	 * \brief Returns the distance between two given entities.
	 * \param Reference to the entity system containing components.
	 * \param ID of the first entity.
	 * \param ID of the second entity.
	 */
	tdt::real get_distance(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the size of the angle bewteen two given vectors as tdt::real
	 *        which can then be used in Ogre::Radian constructor for conversion to Radians.
	 *        (The reason for this is that Lua does not have the notion of radians and as such
	 *        using floating point numbers is easier.)
	 * \param Vector #1.
	 * \param Vector #2.
	 */
	tdt::real get_angle(Ogre::Vector3, Ogre::Vector3);

	/**
	 * \brief Sets the position of a given entity disregarding it's Y coordinate.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new position (vector2 containing the x and z coordinates.)
	 */
	void set_2d_position(EntitySystem&, tdt::uint, Ogre::Vector2);

	/**
	 * \brief Returns the X and Z coordinates of a given entity's position.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \note Cannot use const reference like in the usual get_position function
	 *       because this method creates a proxy Vector2 which cannot be passed
	 *       as an lvalue reference due to it being a temporary object.
	 */
	Ogre::Vector2 get_2d_position(EntitySystem&, tdt::uint);
}