#pragma once

#include "Typedefs.hpp"
#include "Enums.hpp"
class EntitySystem;
class SelectionBox;
class CombatSystem;

/**
 *
 */
namespace CommandHelper
{
	/**
	 *
	 */
	void set_command(EntitySystem&, tdt::uint, COMMAND_TYPE, bool = true);

	/**
	 *
	 */
	bool test_command(EntitySystem&, tdt::uint, COMMAND_TYPE);

	/**
	 * Brief: Commands the miner with the smallest task queue (if any) to mine
	 *        all selected mineable entities.
	 */
	void command_to_mine(EntitySystem&, SelectionBox&);

	/**
	 * Brief: Commands the combat unit with the smallest task queue (if any)
	 *        to attack a selected enemy.
	 */
	void command_to_attack(EntitySystem&, SelectionBox&);

	/**
	 * Brief: Commands the unit with the smallest task queue (if any) to move
	 *        to a given position.
	 */
	void command_to_reposition(EntitySystem&, Ogre::Real, Ogre::Real);

	/**
	 * Brief: Commands all miners that have gold on them to return it to the
	 *        nearest gold vault.
	 */
	void command_to_return_gold(EntitySystem&, CombatSystem&);

	/**
	 * Brief: Commands all free units created at a spawner to return back.
	 */
	void command_to_fall_back(EntitySystem&);
}