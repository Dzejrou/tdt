#pragma once

#include <string>
#include <cstdlib>
class EntitySystem;

namespace InputHelper
{
	/**
	 * Brief: Changes the name of the table that contains a given
	 *        entity's input handler.
	 * Param: Reference to the entity system containing components.
	 * Param: Name of the new input handler (Lua function).
	 * Note: The handler recieves the ID of the entity and the key number when it's called, for current
	 *       keybindings use the game.enum.input Lua table.
	 */
	void set_input_handler(EntitySystem&, std::size_t, const std::string&);

	/**
	 * Brief: Returns name of the table that contains the input handling function
	 *        of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	const std::string& get_input_handler(EntitySystem&, std::size_t);
}