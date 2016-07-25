#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management
 * of the experience value component.
 */
namespace ExperienceValueHelper
{
	/**
	 * \brief Sets the experience value a given entity is worth.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new experience value.
	 */
	void set(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the experience value a given entity is worth.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get(EntitySystem&, tdt::uint);

	/**
	 * \brief Increases the experience value a given entity is worth
	 *        by a given value.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The value to increase by.
	 */
	void increase(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Decreases the experience value a given entity is worth
	 *        by a given value.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The value to decrease by.
	 */
	void decrease(EntitySystem&, tdt::uint, tdt::uint);
}