#pragma once

#include <string>
#include <cstdlib>
#include <deque>
class EntitySystem;

namespace PathfindingHelper
{
	/**
	 * Brief: Returns constant reference to the pathfinding blueprint of a given entity.
	 *        (Which is used for the can_pass & can_break methods in lua.)
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_pathpfinding_blueprint(EntitySystem&, std::size_t);

	/**
	 * Brief: Changes the pathfinding blueprint of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: Name of the new blueprint table.
	 */
	void set_pathfinding_blueprint(EntitySystem&, std::size_t, const std::string&);

	/**
	 * Brief: Returns the node queue of a given entity's path.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	std::deque<std::size_t>& get_path(EntitySystem&, std::size_t);
}