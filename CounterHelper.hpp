#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with counter component
 * management.
 */
namespace CounterHelper
{
	/**
	 * Brief: Increments the counter of a given entity and
	 *        returns true if the counter has reached the max
	 *        value, false otherwise.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	bool increment(EntitySystem&, tdt::uint);

	/**
	 * Brief: Decrements the counter of a given entity and
	 *        returns true if the counter has reached the max
	 *        value, false otherwise.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	bool decrement(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the current value of the counter of a given
	 *        entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new counter value.
	 */
	void set_curr_value(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the current value of the counter of a given
	 *        entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_curr_value(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the max value of the counter of a given
	 *        entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	void set_max_value(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the max value of the counter of a given
	 *        entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_max_value(EntitySystem&, tdt::uint);
}