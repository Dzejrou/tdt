#pragma once

#include <Ogre.h>
#include <vector>
#include <array>
#include <tuple>
#include <numeric>
#include <set>
#include <algorithm>
#include <deque>
#include <cstdlib>
#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "Console.hpp"
#include "SelectionBox.hpp"
#include "Helpers.hpp"
#include "Pathfinding.hpp"
#include "PathfindingAlgorithms.hpp"
#include "Grid.hpp"

/**
 * Represents the pathfinding graph used by the game and provides
 * several methods related to pathfinding that can be used in Lua.
 */
class GridSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's entity system.
		 * Param: Reference to the game's main scene manager.
		 * TODO: Add a reference to the SceneNode holding the ground plane (to easily set scale
		 *       when creating a graph on it).
		 */
		GridSystem(EntitySystem&, Ogre::SceneManager&);

		/**
		 * Destructor.
		 */
		~GridSystem() {}

		/**
		 * Brief: Checks if any nodes were freed or unfreed and if so, corrects
		 *        any path that had those nodes in it.
		 * Param: Time since the last frame.
		 */
		void update(Ogre::Real);

		/**
		 * Brief: Creates and initializes Ogre models for nodes, which allows the developer
		 *        to display them for testing purposes.
		 */
		void create_graphics();

		/**
		 * Brief: Deletes Ogre models of all nodes.
		 */
		void delete_graphics();

		/**
		 * Brief: Changes the visibility status of the nodes if the graphics have been
		 *        created already, does nothing otherwise.
		 * Param: The new visibility status.
		 */
		void set_visible(bool);

		/**
		 * Brief: Returns true if the the grid models are visible, false otherwise.
		 */
		bool is_visible() const;

		/**
		 * Brief: Places a structure (building, wall...) by changing the nodes it
		 *        is placed on to not free, managing residences etc.
		 * Param: ID of the structure.
		 * Param: ID of the central node.
		 * Param: Radius of the structure.
		 */
		void place_structure(std::size_t, std::size_t, std::size_t);
	private:
		/**
		 * Brief: Updates the nodes resident's alignment (if possible)
		 *        when it's neighbour was freed/unfreed.
		 * Param: ID of the node.
		 */
		void update_neighbours_(std::size_t);

		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;

		/**
		 * Reference to the game's main scene manager (used for graphics creation).
		 */
		Ogre::SceneManager& scene_mgr_;

		/**
		 * Determine if the graphics have been loaded and
		 * if the graph is visible (which is only relevant if the former
		 * is true).
		 */
		bool graphics_loaded_, graph_visible_;
};