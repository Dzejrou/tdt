#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with counter component
 * management.
 */
namespace CounterHelper
{
	/**
	 * \brief Increments the counter of a given entity and
	 *        returns true if the counter has reached the max
	 *        value, false otherwise.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	bool increment(EntitySystem&, tdt::uint);

	/**
	 * \brief Decrements the counter of a given entity and
	 *        returns true if the counter has reached the max
	 *        value, false otherwise.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	bool decrement(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the current value of the counter of a given
	 *        entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new counter value.
	 */
	void set_curr_value(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the current value of the counter of a given
	 *        entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_curr_value(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the max value of the counter of a given
	 *        entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	void set_max_value(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the max value of the counter of a given
	 *        entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_max_value(EntitySystem&, tdt::uint);
}