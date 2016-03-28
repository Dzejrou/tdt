#pragma once

#include "Typedefs.hpp"
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
	void set_capacity(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the amount of max mana this entity adds
	 *        to the player's mana capacity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_capacity(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the amount of mana regen this entity adds
	 *        to the player's total mana regen.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new capacity value.
	 */
	void set_regen(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Sets the amount of mana regen this entity adds
	 *        to the player's total mana regen.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_regen(EntitySystem&, tdt::uint);
}