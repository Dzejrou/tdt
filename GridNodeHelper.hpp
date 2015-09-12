#pragma once

#include <cstdlib>
#include <array>
#include <tuple>
#include "Components.hpp"
#include "Util.hpp"
class EntitySystem;
class SelectionBox;

namespace GridNodeHelper
{
	/**
	 * Brief: Returns an array containing IDs of all neighbours of a given node.
	 * Param: EntitySystem containing the node.
	 * Param: ID of the node.
	 */
	const std::array<std::size_t, GridNodeComponent::neighbour_count>& get_neighbours(EntitySystem&, std::size_t);

	/**
	 * Brief: Returns true if the given node is free (duh...), false otherwise.
	 * Param: EntitySystem containing the node.
	 * Param: ID of the node.
	 */
	bool is_free(EntitySystem&, std::size_t);

	/**
	 * Brief: Returns true if a given area (specified by a center node and a radius)
	 *        is free.
	 * Param: EntitySystem containing the nodes in the area.
	 * Param: ID of the center node.
	 * Param: Radius of the area.
	 */
	bool area_free(EntitySystem&, std::size_t, std::size_t = 1);

	/**
	 * Brief: Sets the free status of a given node.
	 * Param: EntitySystem containing the node.
	 * Param: ID of the node.
	 * Param: True for free, false for not-so-free.
	 */
	void set_free(EntitySystem&, std::size_t, bool);

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
	std::tuple<std::size_t, std::size_t> get_board_coords(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the resident of a given node. (Resident is an entity that
	 *        is causing the node to be not free - like a wall, building etc.)
	 * Param: EntitySystem containing the node and the resident.
	 * Param: ID of the node.
	 * Param: ID of the resident.
	 */
	void set_resident(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the resident of a given node.
	 * Param: ID of the node.
	 */
	std::size_t get_resident(EntitySystem&, std::size_t);

	/**
	 * Brief: Returns the manhattan (definition available on Wikipedia...) distance
	 *        between two nodes.
	 * Param: EntitySystem containing the nodes.
	 * Param: ID of the source node.
	 * Param: ID of the target node.
	 */
	std::size_t get_manhattan_distance(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the closest node in a given direction.
	 * Param: EntitySystem containing the node.
	 * Param: ID of the entity that is looking for the node.
	 * Param: The direction represented by the DIRECTION::VAL enum.
	 */
	std::size_t get_node_in_dir(EntitySystem&, std::size_t, int);
}