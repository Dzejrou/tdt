#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the explosion component.
 */
namespace ExplosionHelper
{
	/**
	 * Brief: Sets the value by which a given entity's explosion
	 *        radius is updated on each of the graphics system updates.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new delta value.
	 */
	void set_delta(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the value by which a given entity's explosion
	 *        radius is updated on each of the graphics system updates.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_delta(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the radius after which a given entity with an explosion
	 *        component gets deleted.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new max radius value.
	 */
	void set_max_radius(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the radius after which a given entity with an explosion
	 *        component gets deleted.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_max_radius(EntitySystem&, tdt::uint);

	/**
	 * Brief: Returns the current radius of a given entity's explosion
	 *        component.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_curr_radius(EntitySystem&, tdt::uint);

	/**
	 * Brief: Increases the radius of a given entity's explosion
	 *        component by a given value.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The value to increase by.
	 */
	void increase_curr_radius(EntitySystem&, tdt::uint, tdt::real);
}