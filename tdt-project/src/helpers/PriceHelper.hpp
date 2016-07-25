#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the price component.
 */
namespace PriceHelper
{
	/**
	 * \brief Sets the price of a given entity.
	 * \param Entity system that contains the entity.
	 * \param ID of the entity.
	 * \param The new price.
	 */
	void set_price(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the price of a given entity.
	 * \param Entity system that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_price(EntitySystem&, tdt::uint);
}