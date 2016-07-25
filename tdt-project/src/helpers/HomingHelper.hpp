#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the homing component.
 */
namespace HomingHelper
{
	/**
	 * \brief Sets the ID of the source (entity that shot it) of a given
	 *        projectile.
	 * \param Reference to the entity system containing components.
	 * \param ID of the projectile.
	 * \param ID of the source.
	 */
	void set_source(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the ID of the entity that shot a given projectile.
	 * \param Reference to the entity system containing components.
	 * \param ID of the projectile.
	 */
	tdt::uint get_source(EntitySystem&, tdt::uint);

	/**
	 * \brief Changes the target of a given homing projectile.
	 * \param Reference to the entity system containing components.
	 * \param ID of the projectile.
	 * \param ID of the target.
	 */
	void set_target(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the ID of the target of a given homing projectile.
	 * \param Reference to the entity system containing components.
	 * \param ID of the projectile.
	 */
	tdt::uint get_target(EntitySystem&, tdt::uint);

	/**
	 * \brief Changes the damage of a given homing
	 *        projectile.
	 * \param Reference to the entity system containing components.
	 * \param ID of the projectile.
	 * \param The new damage value.
	 */
	void set_dmg(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the damage value of a given projectile.
	 * \param Reference to the entity system containing components.
	 * \param ID of the projectile.
	 */
	tdt::uint get_dmg(EntitySystem&, tdt::uint);
}