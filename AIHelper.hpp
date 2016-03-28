#pragma once

#include <string>
#include "Enums.hpp"
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the ai component.
 */
namespace AIHelper
{
	/**
	 * Brief: Changes the blueprint table name of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Name of the new blueprint table.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * Brief: Returns name of the blueprint table of a given entity (i.e. the table containing
	 *        it's init, update and finnish methods).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * Brief: Changes the state of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: New state.
	 */
	void set_state(EntitySystem&, tdt::uint, ENTITY_STATE);

	/**
	 * Brief: Returns the state a given entity is in.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	ENTITY_STATE get_state(EntitySystem&, tdt::uint);
}