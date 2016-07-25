#pragma once

#include <Typedefs.hpp>
#include <Enums.hpp>
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
	 * \brief Sets the bit value of a given command for a given entity.
	 * \param Reference to the entity system containing the entity.
	 * \param ID of the entity.
	 * \param Type of the command.
	 * \param The new bit value, true = entity responds to the command type,
	 *        false = entity ignores the command type.
	 */
	void set_command(EntitySystem&, tdt::uint, COMMAND_TYPE, bool = true);

	/**
	 * \brief Returns true if a given entity responds to a given type of
	 *        command, false otherwise.
	 * \param Reference to the entity system containing the entity.
	 * \param ID of the entity.
	 * \param Type of the command.
	 */
	bool test_command(EntitySystem&, tdt::uint, COMMAND_TYPE);

	/**
	 * \brief Commands the miner with the smallest task queue (if any) to mine
	 *        all selected mineable entities.
	 * \param Reference to the entity system containing the entity.
	 * \param Selection box used to select the mineable entities.
	 */
	void command_to_mine(EntitySystem&, SelectionBox&);

	/**
	 * \brief Commands the combat unit with the smallest task queue (if any)
	 *        to attack a selected enemy.
	 * \param Reference to the entity system containing the entity.
	 * \param Selection box used to select the enemy.
	 */
	void command_to_attack(EntitySystem&, SelectionBox&);

	/**
	 * \brief Commands the unit with the smallest task queue (if any) to move
	 *        to a given position.
	 * \param Reference to the entity system containing the entity.
	 * \param X coordinate of the position.
	 * \param Z coordinate of the position.
	 */
	void command_to_reposition(EntitySystem&, Ogre::Real, Ogre::Real);

	/**
	 * \brief Commands all miners that have gold on them to return it to the
	 *        nearest gold vault.
	 * \param Reference to the entity system containing the entity.
	 * \param Combat system used to search for deposits.
	 */
	void command_to_return_gold(EntitySystem&, CombatSystem&);

	/**
	 * \brief Commands all free units created at a spawner to return back.
	 * \param Reference to the entity system containing the entity.
	 */
	void command_to_fall_back(EntitySystem&);
}