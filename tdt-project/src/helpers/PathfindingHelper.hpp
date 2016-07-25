#pragma once

#include <string>
#include <deque>
#include <Enums.hpp>
#include <Typedefs.hpp>
class EntitySystem;
struct PathfindingComponent;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the pathfinding component.
 */
namespace PathfindingHelper
{
	/**
	 * \brief Returns constant reference to the pathfinding blueprint of a given entity.
	 *        (Which is used for the can_pass & can_break methods in lua.)
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_pathpfinding_blueprint(EntitySystem&, tdt::uint);

	/**
	 * \brief Changes the pathfinding blueprint of a given entity.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 * \param Name of the new blueprint table.
	 */
	void set_pathfinding_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the node queue of a given entity's path.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 */
	std::deque<tdt::uint>& get_path(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns true if a given entity can break a structure residing on a given node (if any).
	 * \param ID of the entity.
	 * \param Pathfinding component of the entity.
	 * \param ID of the node.
	 */
	bool can_break(tdt::uint, const PathfindingComponent&, tdt::uint);

	/**
	 * \brief Returns the cost a journey to a given node takes for a given entity.
	 * \param ID of the entity.
	 * \param Pathfinding component of the entity.
	 * \param ID of the node.
	 */
	tdt::real get_cost(tdt::uint, const PathfindingComponent&, tdt::uint, DIRECTION::VAL);
}