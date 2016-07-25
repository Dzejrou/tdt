#pragma once

#include <OGRE/Ogre.h>
#include "System.hpp"
class EntitySystem;

/**
 * Represents the pathfinding graph used by the game and provides
 * several methods related to pathfinding that can be used in Lua.
 */
class GridSystem : public System
{
	public:
		/**
		 * Constructor.
		 * \param Reference to the game's entity system.
		 * \param Reference to the game's main scene manager.
		 */
		GridSystem(EntitySystem&, Ogre::SceneManager&);

		/**
		 * Destructor.
		 */
		~GridSystem() = default;

		/**
		 * \brief Checks if any nodes were freed or unfreed and if so, corrects
		 *        any path that had those nodes in it.
		 * \param Time since the last frame.
		 */
		void update(tdt::real) override;

		/**
		 * \brief Creates and initializes Ogre models for nodes, which allows the developer
		 *        to display them for testing purposes.
		 */
		void create_graphics();

		/**
		 * \brief Deletes Ogre models of all nodes.
		 */
		void delete_graphics();

		/**
		 * \brief Changes the visibility status of the nodes if the graphics have been
		 *        created already, does nothing otherwise.
		 * \param The new visibility status.
		 */
		void set_visible(bool);

		/**
		 * \brief Returns true if the the grid models are visible, false otherwise.
		 */
		bool is_visible() const;

		/**
		 * \brief Places a structure (building, wall...) by changing the nodes it
		 *        is placed on to not free, managing residences etc.
		 * \param ID of the structure.
		 * \param ID of the central node.
		 * \param Radius of the structure.
		 */
		void place_structure(tdt::uint, tdt::uint, tdt::uint);

	private:
		/**
		 * \brief Updates the nodes resident's alignment (if possible)
		 *        when it's neighbour was freed/unfreed.
		 * \param ID of the node.
		 */
		void update_neighbours_(tdt::uint);

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