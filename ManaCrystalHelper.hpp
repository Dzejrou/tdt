#pragma once

#include <cstdlib>
class EntitySystem;

/**
 * Auxiliary namespace that contains functions that help with the management
 * of the mana crystal component.
 */
namespace ManaCrystalHelper
{
	/**
	 * Brief: Sets the amount of max mana this entity adds
	 *        to the player's mana capacity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new capacity value.
	 */
	void set_capacity(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the amount of max mana this entity adds
	 *        to the player's mana capacity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get_capacity(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the amount of mana regen this entity adds
	 *        to the player's total mana regen.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new capacity value.
	 */
	void set_regen(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Sets the amount of mana regen this entity adds
	 *        to the player's total mana regen.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get_regen(EntitySystem&, std::size_t);
}