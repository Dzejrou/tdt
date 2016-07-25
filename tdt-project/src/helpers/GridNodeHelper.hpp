#pragma once

#include <array>
#include <tuple>
#include <Typedefs.hpp>
#include <Components.hpp>
class EntitySystem;
class SelectionBox;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the grid node component.
 */
namespace GridNodeHelper
{
	/**
	 * \brief Returns an array containing IDs of all neighbours of a given node.
	 * \param EntitySystem containing the node.
	 * \param ID of the node.
	 */
	const std::array<tdt::uint, GridNodeComponent::neighbour_count>& get_neighbours(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns true if the given node is free (duh...), false otherwise.
	 * \param EntitySystem containing the node.
	 * \param ID of the node.
	 */
	bool is_free(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns true if a given area (specified by a center node and a radius)
	 *        is free.
	 * \param EntitySystem containing the nodes in the area.
	 * \param ID of the center node.
	 * \param Radius of the area.
	 * \note This counts also walkthrough buildings, as it's only used for building
	 *       placing and not pathfinding.
	 */
	bool area_free(EntitySystem&, tdt::uint, tdt::uint = 1);

	/**
	 * \brief Sets the free status of a given node.
	 * \param EntitySystem containing the node.
	 * \param ID of the node.
	 * \param True for free, false for not-so-free.
	 */
	void set_free(EntitySystem&, tdt::uint, bool);

	/**
	 * \brief Applies the GridSystem::set_free method to all currently
	 *        selected nodes.
	 * \param EntitySystem containing the nodes.
	 * \param Reference to the selection box that selected the nodes.
	 * \param True for free, false for not-so-free.
	 */
	void set_free_selected(EntitySystem&, SelectionBox&, bool);

	/**
	 * \brief Returns the board relative coordinates (row & column)
	 *        of a given node.
	 * \param EntitySystem containing the node.
	 * \param ID of the node.
	 */
	std::tuple<tdt::uint, tdt::uint> get_board_coords(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the resident of a given node. (Resident is an entity that
	 *        is causing the node to be not free - like a wall, building etc.)
	 * \param EntitySystem containing the node and the resident.
	 * \param ID of the node.
	 * \param ID of the resident.
	 */
	void set_resident(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the resident of a given node.
	 * \param ID of the node.
	 */
	tdt::uint get_resident(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns the manhattan (definition available on Wikipedia...) distance
	 *        between two nodes.
	 * \param EntitySystem containing the nodes.
	 * \param ID of the source node.
	 * \param ID of the target node.
	 */
	tdt::uint get_manhattan_distance(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the closest node in a given direction.
	 * \param EntitySystem containing the node.
	 * \param ID of the entity that is looking for the node.
	 * \param The direction represented by the DIRECTION::VAL enum.
	 */
	tdt::uint get_node_in_dir(EntitySystem&, tdt::uint, int);

	/**
	 * \brief Sets the portal node linked to this node. 
	 * \param EntitySystem containing the node.
	 * \param ID of this node.
	 * \param ID of the portal node.
	 */
	void set_portal_neighbour(EntitySystem&, tdt::uint, tdt::uint);
}