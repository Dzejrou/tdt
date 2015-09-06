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

/**
 * Represents the pathfinding graph used by the game and provides
 * several methods related to pathfinding that can be used in Lua.
 */
class GridSystem : public System
{
	/**
	 * GameSerializer is a friend class so that it can easily access the grid realted data
	 * (like dimensions and node distance) when saving the game.
	 */
	friend class GameSerializer;
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
		 * TODO:
		 */
		void update(Ogre::Real);

		/**
		 * Brief: Creates a new grid node at a given position, then returns
		 *        it's ID.
		 * Param: The X axis coordinate.
		 * Param: The Y axis coordinate.
		 * Param: The Z axis coordinate.
		 */
		std::size_t add_node(Ogre::Real, Ogre::Real, Ogre::Real);

		/**
		 * Brief: Generates a grid graph with the given parameters to be used for
		 *        pathfinding.
		 * Param: Width of the graph (in node count).
		 * Param: Height of the graph (in node count).
		 * Param: Distance between adjascent nodes.
		 * Param: X axis coordinate of the start point.
		 * Param: Z axis coordinate of the start point.
		 */
		void create_graph(std::size_t, std::size_t, Ogre::Real, Ogre::Real, Ogre::Real);

		/**
		 * Brief: Returns the ID of a node at a given position in the grid.
		 * Param: Column number.
		 * Param: Row number.
		 */
		std::size_t get_node(std::size_t, std::size_t) const;

		/**
		 * Brief: Returns the ID of a node that is closed to a given world coorinate.
		 * Param: X axis coordinate.
		 * Param: Z axis coordinate.
		 * Note: Adding the ability to specify in what direction the node must be might
		 *       be beneficial for pathfinding.
		 */
		std::size_t get_node_from_position(Ogre::Real, Ogre::Real) const;

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
		 * Brief: Returns an array containing IDs of all neighbours of a given node.
		 * Param: ID of the node.
		 */
		std::array<std::size_t, 8> get_neighbours(std::size_t) const;

		/**
		 * Brief: Returns true if the given node is free (duh...), false otherwise.
		 * Param: ID of the node.
		 */
		bool is_free(std::size_t) const;

		/**
		 * Brief: Returns true if a given area (specified by a center node and a radius)
		 *        is free.
		 * Param: ID of the center node.
		 * Param: Radius of the area.
		 */
		bool area_free(std::size_t, std::size_t = 1) const;

		/**
		 * Brief: Sets the free status of a given node.
		 * Param: True for free, false for not-so-free.
		 */
		void set_free(std::size_t, bool);

		/**
		 * Brief: Applies the GridSystem::set_free method to all currently
		 *        selected nodes.
		 * Param: Reference to the selection box that selected the nodes.
		 * Param: True for free, false for not-so-free.
		 */
		void set_free_selected(SelectionBox&, bool);

		/**
		 * Brief: Returns the manhattan (definition available on Wikipedia...) distance
		 *        between two nodes.
		 * Param: ID of the source node.
		 * Param: ID of the target node.
		 */
		std::size_t get_manhattan_distance(std::size_t, std::size_t) const;

		/**
		 * Brief: Performs pathfinding for a given entity to a given target
		 *        and adds the path to the entity's pathfinding component.
		 * Param: ID of the entity.
		 * Param: ID of the target.
		 * Param: If true, the path will be added to the entity's pathfinding component,
		 *        otherwise will just return if the target is reachable.
		 */
		bool perform_a_star(std::size_t, std::size_t, bool = true);

		/**
		 * TODO: Implement this mechanic.
		 */
		bool can_pass(std::size_t, std::size_t) const;

		/**
		 * Brief: Returns the board relative coordinates (row & column)
		 *        of a given node.
		 * Param: ID of the node.
		 */
		std::tuple<std::size_t, std::size_t> get_board_coords(std::size_t) const;

		/**
		 * Brief: Resets the colour of path nodes back to blue if the graphics
		 *        are enabled, does nothing otherwise.
		 */
		void clear_path_colour();

		/**
		 * Brief: Places a structure (building, wall...) by changing the nodes it
		 *        is placed on to not free, managing residences etc.
		 */
		void place_structure(std::size_t, std::size_t, std::size_t);

		/**
		 * Brief: Sets the resident of a given node. (Resident is an entity that
		 *        is causing the node to be not free - like a wall, building etc.)
		 * Param: ID of the node.
		 * Param: ID of the resident.
		 */
		void set_resident(std::size_t, std::size_t);

		/**
		 * Brief: Returns the resident of a given node.
		 * Param: ID of the node.
		 */
		std::size_t get_resident(std::size_t) const;

		std::size_t get_node_in_dir(std::size_t, int) const;
	private:
		/**
		 * TODO: Implement this mechanic.
		 */
		bool can_break_(std::size_t, PathfindingComponent&, std::size_t) const;

		/**
		 *
		 */
		std::deque<std::size_t> get_path_(std::size_t, std::size_t, std::size_t);
		/**
		 * Brief: Returns true if a given entity is on the board (that is, is an actual node).
		 * Param: ID of the entity.
		 * Note: Nodes have incremental IDs as they are created first and after each other,
		 *       if this is changed in the future, this method needs to be also changed accordingly.
		 */
		bool in_board_(std::size_t) const;

		/**
		 * Brief: Generates a neighbour list for a given node (thus linking it to the graph).
		 * Param: ID of the node.
		 * Param: Auxuliary vector containing component pointers for fast access.
		 *       (This method will ever be called only in the GridSystem::create_graph method,
		 *        which already has such a vector and so it's used here too.)
		 */
		void link_(std::size_t, std::vector<GridNodeComponent*>&);

		/**
		 * Brief: Returns the absolute value of a given integer - this is used to avoid
		 *        all the explicit conversions to std::size_t as the std::abs and
		 *        Ogre::Math::Abs functions return int and Ogre::Real (both signed) respectively.
		 */
		std::size_t abs_(int) const;

		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;

		/**
		 * Reference to the game's main scene manager (used for graphics creation).
		 */
		Ogre::SceneManager& scene_mgr_;

		/**
		 * Dimensions of the grid in node count.
		 * (Actual dimensions = dimensions * distance.)
		 */
		std::size_t width_, height_;

		/**
		 * Coordinates of the starting node of the grid.
		 * (This 2D vector contains X and Z coordinates despite it's second member
		 *  being names Y).
		 */
		Ogre::Vector2 start_;

		/**
		 * Distance between two adjascent nodes.
		 */
		Ogre::Real distance_;

		/**
		 * Vector containing the IDs of the nodes in the grid, basically
		 * representing a 2D matrix stored in a 1D container.
		 */
		std::vector<std::size_t> board_;

		/**
		 * Determine if the graphics have been loaded and
		 * if the graph is visible (which is only relevant if the former
		 * is true).
		 */
		bool graphics_loaded_, graph_visible_;

		/**
		 * Auxiliary vectors containing IDs of the nodes that have been
		 * freed/unfreed on last frame. Used for pathfinding correction
		 * and structure model changes.
		 */
		std::vector<std::size_t> freed_, unfreed_;
};