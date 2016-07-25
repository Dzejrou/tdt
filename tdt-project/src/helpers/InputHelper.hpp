#pragma once

#include <string>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the input component.
 */
namespace InputHelper
{
	/**
	 * \brief Changes the name of the table that contains a given
	 *        entity's input handler.
	 * \param Reference to the entity system containing components.
	 * \param Name of the new input handler (Lua function).
	 * \note The handler recieves the ID of the entity and the key number when it's called, for current
	 *       keybindings use the game.enum.input Lua table.
	 */
	void set_input_handler(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns name of the table that contains the input handling function
	 *        of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	const std::string& get_input_handler(EntitySystem&, tdt::uint);
}