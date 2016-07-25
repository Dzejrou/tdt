#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the explosion component.
 */
namespace ExplosionHelper
{
	/**
	 * \brief Sets the value by which a given entity's explosion
	 *        radius is updated on each of the graphics system updates.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new delta value.
	 */
	void set_delta(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the value by which a given entity's explosion
	 *        radius is updated on each of the graphics system updates.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_delta(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the radius after which a given entity with an explosion
	 *        component gets deleted.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new max radius value.
	 */
	void set_max_radius(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the radius after which a given entity with an explosion
	 *        component gets deleted.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_max_radius(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns the current radius of a given entity's explosion
	 *        component.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_curr_radius(EntitySystem&, tdt::uint);

	/**
	 * \brief Increases the radius of a given entity's explosion
	 *        component by a given value.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The value to increase by.
	 */
	void increase_curr_radius(EntitySystem&, tdt::uint, tdt::real);
}