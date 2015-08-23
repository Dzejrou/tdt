#pragma once

#include <string>
class AIComponent;
class EntitySystem;

namespace AIHelper
{
	/**
	 * Brief: Changes the blueprint table name of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Name of the new blueprint table.
	 */
	void set_blueprint(EntitySystem&, std::size_t, const std::string&);

	/**
	 * Brief: Returns name of the blueprint table of a given entity (i.e. the table containing
	 *        it's init, update and finnish methods).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, std::size_t);

	/**
	 * Brief: Changes the FACTION of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: New FACTION.
	 */
	void set_faction(EntitySystem&, std::size_t, FACTION);

	/**
	 * Brief: Returns the FACTION of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	FACTION get_faction(EntitySystem&, std::size_t);

	/**
	 * Brief: Changes the state of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: New state.
	 */
	void set_state(EntitySystem&, std::size_t, ENTITY_STATE);

	/**
	 * Brief: Returns the state a given entity is in.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	ENTITY_STATE get_state(EntitySystem&, std::size_t);
}