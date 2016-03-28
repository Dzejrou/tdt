#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace that contains functions that help with the management
 * of the mana component.
 */
namespace ManaHelper
{
	/**
	 * Brief: Adds a given amount of mana to a given entity's
	 *        current mana pool.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: Amount of mana to add.
	 */
	void add_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Removes a given amount of mana from a given entity's
	 *        current mana pool.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: Amount of mana to subtract.
	 */
	bool sub_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Sets the amount of mana a given entity has to a given
	 *        amount.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new amount of mana.
	 */
	void set_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the amount of mana a given entity has.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_mana(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the max amount of mana a given entity can have.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new mana limit.
	 */
	void set_max_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the max amount of mana a given entity can have.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_max_mana(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the mana regeneration value of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new mana regeneration value.
	 */
	void set_regen(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the mana regeneration value of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_regen(EntitySystem&, tdt::uint);

}