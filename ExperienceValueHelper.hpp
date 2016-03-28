#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management
 * of the experience value component.
 */
namespace ExperienceValueHelper
{
	/**
	 * Brief: Sets the experience value a given entity is worth.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new experience value.
	 */
	void set(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the experience value a given entity is worth.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get(EntitySystem&, tdt::uint);

	/**
	 * Brief: Increases the experience value a given entity is worth
	 *        by a given value.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The value to increase by.
	 */
	void increase(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Decreases the experience value a given entity is worth
	 *        by a given value.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The value to decrease by.
	 */
	void decrease(EntitySystem&, tdt::uint, tdt::uint);
}