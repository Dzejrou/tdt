#pragma once

#include <Ogre.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "Helpers.hpp"
#include "Enums.hpp"

/**
 * Class representing the pathfinding grid.
 */
class Grid
{
	/**
	 * GameSerializer is a friend class so that it can easily access the grid realted data
	 * (like dimensions and node distance) when saving the game.
	 */
	friend class GameSerializer;
	public:
		/**
		 * Brief: Returns true if a given node is in the grid.
		 * Param: ID of the node.
		 */
		bool in_board(std::size_t) const;

		/**
		 * Brief: Returns a constant reference to the list of
		 *        freed nodes.
		 */
		const std::vector<std::size_t>& get_freed() const;

		/**
		 * Brief: Returns a constant reference to the list of
		 *        unfreed nodes.
		 */
		const std::vector<std::size_t>& get_unfreed() const;

		/**
		 * Brief: Removes all nodes from the list of freed nodes.
		 */
		void clear_freed();

		/**
		 * Brief: Removes all nodes from the list of unfreed nodes.
		 */
		void clear_unfreed();

		/**
		 * Brief: Created a new node at the given position.
		 * Param: EntitySystem that contains the node.
		 * Param: 2D position of the node.
		 */
		std::size_t add_node(EntitySystem&, Ogre::Vector2);

		/**
		 * Brief: Adds a given node to the list of the freed nodes.
		 * Param: ID of the node.
		 */
		void add_freed(std::size_t);

		/**
		 * Brief: Adds a given node to the list of the unfreed nodes.
		 * Param: ID of the node.
		 */
		void add_unfreed(std::size_t);

		/**
		 * Brief: Removes a given node from the node list.
		 * Param: ID of the node.
		 * TODO: Possibly implement "unlink"?
		 */
		void remove_node(std::size_t);

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
		 * Brief: Generates a grid graph with the given parameters to be used for
		 *        pathfinding.
		 * Param: EntitySystem that will contain the nodes.
		 * Param: Starting position (x,z axes) of the grid. 
		 * Param: Width of the graph (in node count).
		 * Param: Height of the graph (in node count).
		 * Param: Distance between adjascent nodes.
		 */
		void create_graph(EntitySystem&, Ogre::Vector2, std::size_t, std::size_t, Ogre::Real);

		/**
		 * Brief: Returns the distance between two nodes in the four non-diagonal
		 *        directions.
		 */
		Ogre::Real get_distance() const;

		/**
		 * Brief: Returns a reference to the static instance of this class.
		 * Note: Handles initialization and safe destruction by itself.
		 * TODO: Possibly unite this an Lpp::Script under one singleton interface?
		 */
		static Grid& instance();

		/**
		 * Since there should be only one grid at all times accesible from the Grid::instance
		 * method, all copy/move operations are disabled for this class.
		 */
		Grid(const Grid&) = delete;
		Grid& operator=(const Grid&) = delete;
		Grid(Grid&&) = delete;
		Grid& operator=(Grid&&) = delete;
	private:
		/**
		 * Constructor. 
		 * Kept private since there should be only one grid at all times.
		 */
		Grid() = default;

		/**
		 * Destructor.
		 */
		~Grid() {}

		/**
		 * Brief: Generates a neighbour list for a given node (thus linking it to the graph).
		 * Param: ID of the node.
		 * Param: Auxuliary vector containing component pointers for fast access.
		 *       (This method will ever be called only in the GridSystem::create_graph method,
		 *        which already has such a vector and so it's used here too.)
		 */
		void link_(std::size_t, std::vector<GridNodeComponent*>&);

		/**
		 * Vector containing the IDs of the nodes in the grid, basically
		 * representing a 2D matrix stored in a 1D container.
		 */
		std::vector<std::size_t> nodes_;

		/**
		 * Auxiliary vectors containing IDs of the nodes that have been
		 * freed/unfreed on last frame. Used for pathfinding correction
		 * and structure model changes.
		 */
		std::vector<std::size_t> freed_, unfreed_;

		/**
		 * Dimensions of the grid in node count.
		 * (Actual dimensions = dimensions * distance.)
		 */
		std::size_t width_, height_;

		/**
		 * Distance between two adjascent nodes.
		 */
		Ogre::Real distance_;

		/**
		 * ID of the first node, this allows for the node IDs to be outside the
		 * (0, width_ * height_) range,
		 */
		std::size_t starting_index_;

		/**
		 * Coordinates of the starting node of the grid.
		 * (This 2D vector contains X and Z coordinates despite it's second member
		 *  being names Y).
		 */
		Ogre::Vector2 start_;
};