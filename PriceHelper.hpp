#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the price component.
 */
namespace PriceHelper
{
	/**
	 * Brief: Sets the price of a given entity.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new price.
	 */
	void set_price(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the price of a given entity.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_price(EntitySystem&, tdt::uint);
}