#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the limited life span component.
 */
namespace LimitedLifeSpanHelper
{
	/**
	 * \brief Sets the life span of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new life span.
	 */
	void set_max_time(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the life span of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_max_time(EntitySystem&, tdt::uint);

	/**
	 *
	 * \brief Returns the life time of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_curr_time(EntitySystem&, tdt::uint);

	/**
	 * \brief Advances the life time of a given entity by a given value.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The value to advance by.
	 */
	void advance_curr_time(EntitySystem&, tdt::uint, tdt::real);
}