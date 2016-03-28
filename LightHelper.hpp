#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the light component.
 */
namespace LightHelper
{
	/**
	 * Brief: Sets the visibility status of a given light entity.
	 * Param: Entity system that contains the light entity.
	 * Param: ID of the entity.
	 * Param: The new visibility status (true for visible).
	 */
	void set_visible(EntitySystem&, tdt::uint, bool);

	/**
	 * Brief: Toggles (visible -> invisible and vice versa) the visibility
	 *        status of a given light entity.
	 * Param: Entity system that contains the light entity.
	 * Param: ID of the entity.
	 */
	void toggle_visible(EntitySystem&, tdt::uint);

	/**
	 * Brief: Returns the visibility status of a given light entity.
	 * Param: Entity system that contains the light entity.
	 * Param: ID of the entity.
	 */
	bool is_visible(EntitySystem&, tdt::uint);

	/**
	 * Brief: Performs OGRE initialization of the light component of a given entity,
	 *        used when loading a saved game.
	 * Param: Entity system that contains the light entity.
	 * Param: ID of the entity.
	 */
	void init(EntitySystem&, tdt::uint);
}