#pragma once

#include "Typedefs.hpp"
#include "Enums.hpp"
class EntitySystem;
class SelectionBox;
class CombatSystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the command component.
 */
namespace CommandHelper
{
	/**
	 * Brief: Sets the bit value of a given command for a given entity.
	 * Param: Reference to the entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: Type of the command.
	 * Param: The new bit value, true = entity responds to the command type,
	 *        false = entity ignores the command type.
	 */
	void set_command(EntitySystem&, tdt::uint, COMMAND_TYPE, bool = true);

	/**
	 * Brief: Returns true if a given entity responds to a given type of
	 *        command, false otherwise.
	 * Param: Reference to the entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: Type of the command.
	 */
	bool test_command(EntitySystem&, tdt::uint, COMMAND_TYPE);

	/**
	 * Brief: Commands the miner with the smallest task queue (if any) to mine
	 *        all selected mineable entities.
	 * Param: Reference to the entity system containing the entity.
	 * Param: Selection box used to select the mineable entities.
	 */
	void command_to_mine(EntitySystem&, SelectionBox&);

	/**
	 * Brief: Commands the combat unit with the smallest task queue (if any)
	 *        to attack a selected enemy.
	 * Param: Reference to the entity system containing the entity.
	 * Param: Selection box used to select the enemy.
	 */
	void command_to_attack(EntitySystem&, SelectionBox&);

	/**
	 * Brief: Commands the unit with the smallest task queue (if any) to move
	 *        to a given position.
	 * Param: Reference to the entity system containing the entity.
	 * Param: X coordinate of the position.
	 * Param: Z coordinate of the position.
	 */
	void command_to_reposition(EntitySystem&, Ogre::Real, Ogre::Real);

	/**
	 * Brief: Commands all miners that have gold on them to return it to the
	 *        nearest gold vault.
	 * Param: Reference to the entity system containing the entity.
	 * Param: Combat system used to search for deposits.
	 */
	void command_to_return_gold(EntitySystem&, CombatSystem&);

	/**
	 * Brief: Commands all free units created at a spawner to return back.
	 * Param: Reference to the entity system containing the entity.
	 */
	void command_to_fall_back(EntitySystem&);
}