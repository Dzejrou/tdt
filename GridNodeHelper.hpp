#pragma once

#include <array>
#include <tuple>
#include "Typedefs.hpp"
#include "Components.hpp"
class EntitySystem;
class SelectionBox;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the grid node component.
 */
namespace GridNodeHelper
{
	/**
	 * Brief: Returns an array containing IDs of all neighbours of a given node.
	 * Param: EntitySystem containing the node.
	 * Param: ID of the node.
	 */
	const std::array<tdt::uint, GridNodeComponent::neighbour_count>& get_neighbours(EntitySystem&, tdt::uint);

	/**
	 * Brief: Returns true if the given node is free (duh...), false otherwise.
	 * Param: EntitySystem containing the node.
	 * Param: ID of the node.
	 */
	bool is_free(EntitySystem&, tdt::uint);

	/**
	 * Brief: Returns true if a given area (specified by a center node and a radius)
	 *        is free.
	 * Param: EntitySystem containing the nodes in the area.
	 * Param: ID of the center node.
	 * Param: Radius of the area.
	 * Note: This counts also walkthrough buildings, as it's only used for building
	 *       placing and not pathfinding.
	 */
	bool area_free(EntitySystem&, tdt::uint, tdt::uint = 1);

	/**
	 * Brief: Sets the free status of a given node.
	 * Param: EntitySystem containing the node.
	 * Param: ID of the node.
	 * Param: True for free, false for not-so-free.
	 */
	void set_free(EntitySystem&, tdt::uint, bool);

	/**
	 * Brief: Applies the GridSystem::set_free method to all currently
	 *        selected nodes.
	 * Param: EntitySystem containing the nodes.
	 * Param: Reference to the selection box that selected the nodes.
	 * Param: True for free, false for not-so-free.
	 */
	void set_free_selected(EntitySystem&, SelectionBox&, bool);

	/**
	 * Brief: Returns the board relative coordinates (row & column)
	 *        of a given node.
	 * Param: EntitySystem containing the node.
	 * Param: ID of the node.
	 */
	std::tuple<tdt::uint, tdt::uint> get_board_coords(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the resident of a given node. (Resident is an entity that
	 *        is causing the node to be not free - like a wall, building etc.)
	 * Param: EntitySystem containing the node and the resident.
	 * Param: ID of the node.
	 * Param: ID of the resident.
	 */
	void set_resident(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the resident of a given node.
	 * Param: ID of the node.
	 */
	tdt::uint get_resident(EntitySystem&, tdt::uint);

	/**
	 * Brief: Returns the manhattan (definition available on Wikipedia...) distance
	 *        between two nodes.
	 * Param: EntitySystem containing the nodes.
	 * Param: ID of the source node.
	 * Param: ID of the target node.
	 */
	tdt::uint get_manhattan_distance(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the closest node in a given direction.
	 * Param: EntitySystem containing the node.
	 * Param: ID of the entity that is looking for the node.
	 * Param: The direction represented by the DIRECTION::VAL enum.
	 */
	tdt::uint get_node_in_dir(EntitySystem&, tdt::uint, int);

	/**
	 * Brief: Sets the portal node linked to this node. 
	 * Param: EntitySystem containing the node.
	 * Param: ID of this node.
	 * Param: ID of the portal node.
	 */
	void set_portal_neighbour(EntitySystem&, tdt::uint, tdt::uint);
}