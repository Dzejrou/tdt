#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the movement component.
 */
namespace MovementHelper
{
	/**
	 * \brief Returns the speed modifier of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_speed_modifier(EntitySystem&, tdt::uint);

	/**
	 * \brief Changes the speed modifier of a given entity to a given value.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param New speed value.
	 */
	void set_speed_modifier(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the direction from a given entity to another given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the first entity.
	 * \param ID of the second entity.
	 */
	Ogre::Vector3 dir_to(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the direction a given entity is facing.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	Ogre::Vector3 get_dir(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns the opposite direction to the direction a given entity is facing.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	Ogre::Vector3 get_dir_back(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns the direction perpendicular to the direction a given entity is facing.
	 *        (To the left.)
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	Ogre::Vector3 get_dir_left(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns the direction perpendicular to the direction a given entity is facing.
	 *        (To the right.)
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	Ogre::Vector3 get_dir_right(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the original value of a given entity's speed.
	 *        (Used for serialization.)
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	void set_original_speed(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the original speed of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_original_speed(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the speed of a given entity to it's original value.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	void reset_speed(EntitySystem&, tdt::uint);
}