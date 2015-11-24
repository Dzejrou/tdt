#pragma once

#include <cstdlib>
class EntitySystem;

namespace PriceHelper
{
	/**
	 * Brief: Sets the price of a given entity.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new price.
	 */
	void set_price(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the price of a given entity.
	 * Param: Entity system that contains the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get_price(EntitySystem&, std::size_t);
}