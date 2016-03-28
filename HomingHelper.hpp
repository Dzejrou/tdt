#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the homing component.
 */
namespace HomingHelper
{
	/**
	 * Brief: Sets the ID of the source (entity that shot it) of a given
	 *        projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 * Param: ID of the source.
	 */
	void set_source(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the ID of the entity that shot a given projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 */
	tdt::uint get_source(EntitySystem&, tdt::uint);

	/**
	 * Brief: Changes the target of a given homing projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 * Param: ID of the target.
	 */
	void set_target(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the ID of the target of a given homing projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 */
	tdt::uint get_target(EntitySystem&, tdt::uint);

	/**
	 * Brief: Changes the damage of a given homing
	 *        projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 * Param: The new damage value.
	 */
	void set_dmg(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the damage value of a given projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 */
	tdt::uint get_dmg(EntitySystem&, tdt::uint);
}