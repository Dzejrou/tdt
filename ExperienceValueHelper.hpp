#pragma once

#include <cstdlib>
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
	void set(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the experience value a given entity is worth.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get(EntitySystem&, std::size_t);

	/**
	 * Brief: Increases the experience value a given entity is worth
	 *        by a given value.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The value to increase by.
	 */
	void increase(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Decreases the experience value a given entity is worth
	 *        by a given value.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The value to decrease by.
	 */
	void decrease(EntitySystem&, std::size_t, std::size_t);
}