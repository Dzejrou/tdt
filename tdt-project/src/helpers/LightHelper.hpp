#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the light component.
 */
namespace LightHelper
{
	/**
	 * \brief Sets the visibility status of a given light entity.
	 * \param Entity system that contains the light entity.
	 * \param ID of the entity.
	 * \param The new visibility status (true for visible).
	 */
	void set_visible(EntitySystem&, tdt::uint, bool);

	/**
	 * \brief Toggles (visible -> invisible and vice versa) the visibility
	 *        status of a given light entity.
	 * \param Entity system that contains the light entity.
	 * \param ID of the entity.
	 */
	void toggle_visible(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns the visibility status of a given light entity.
	 * \param Entity system that contains the light entity.
	 * \param ID of the entity.
	 */
	bool is_visible(EntitySystem&, tdt::uint);

	/**
	 * \brief Performs OGRE initialization of the light component of a given entity,
	 *        used when loading a saved game.
	 * \param Entity system that contains the light entity.
	 * \param ID of the entity.
	 */
	void init(EntitySystem&, tdt::uint);
}