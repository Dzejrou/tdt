#pragma once

#include <Ogre.h>
#include <string>
#include <cstdlib>
#include <deque>
#include "lppscript/LppScript.hpp"
#include "Enums.hpp"
class EntitySystem;
struct PathfindingComponent;

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

	/**
	 * Brief: Returns true if a given entity can break a structure residing on a given node (if any).
	 * Param: ID of the entity.
	 * Param: Pathfinding component of the entity.
	 * Param: ID of the node.
	 */
	bool can_break(std::size_t, const PathfindingComponent&, std::size_t);

	/**
	 * Brief: Returns the cost a journey to a given node takes for a given entity.
	 * Param: ID of the entity.
	 * Param: Pathfinding component of the entity.
	 * Param: ID of the node.
	 */
	Ogre::Real get_cost(std::size_t, const PathfindingComponent&, std::size_t, DIRECTION::VAL);
}