#pragma once

#include "Components.hpp"
#include "EntitySystem.hpp"

namespace HomingHelper
{
	/**
	 * Brief: Sets the ID of the source (entity that shot it) of a given
	 *        projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 * Param: ID of the source.
	 */
	void set_source(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the ID of the entity that shot a given projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 */
	std::size_t get_source(EntitySystem&, std::size_t);

	/**
	 * Brief: Changes the target of a given homing projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 * Param: ID of the target.
	 */
	void set_target(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the ID of the target of a given homing projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 */
	std::size_t get_target(EntitySystem&, std::size_t);

	/**
	 * Brief: Changes the damage of a given homing
	 *        projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 * Param: The new damage value.
	 */
	void set_dmg(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the damage value of a given projectile.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the projectile.
	 */
	std::size_t get_dmg(EntitySystem&, std::size_t);
}