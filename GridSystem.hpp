#pragma once

#include <Ogre.h>

#include <vector>
#include <array>
#include <tuple>
#include <numeric>
#include <set>
#include <algorithm>
#include <deque>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "Console.hpp"
#include "SelectionBox.hpp"

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
		 *
		 */
		std::size_t add_node(Ogre::Real, Ogre::Real, Ogre::Real);
		std::size_t add_line(std::size_t, std::size_t);
		void create_graph(std::size_t, std::size_t, Ogre::Real, Ogre::Real, Ogre::Real);
		std::size_t get_node(std::size_t, std::size_t) const;
		std::size_t get_node_from_position(Ogre::Real, Ogre::Real) const;
		void create_graphics();
		void delete_graphics();
		void set_visible(bool);
		bool is_visible() const;

		std::array<std::size_t, 8> get_neighbours(std::size_t) const;
		bool is_free(std::size_t) const;
		void set_free(std::size_t, bool);
		void set_free_selected(SelectionBox&, bool);

		std::size_t get_manhattan_distance(std::size_t, std::size_t) const;

		bool perform_a_star(std::size_t, std::size_t, std::size_t);

		const std::string& get_pathpfinding_blueprint(std::size_t) const;
		void set_pathfinding_blueprint(std::size_t, const std::string&);

		bool can_break(std::size_t, std::size_t) const;
		bool can_pass(std::size_t, std::size_t) const;
		std::tuple<std::size_t, std::size_t> get_board_coords(std::size_t) const;
		void clear_path_colour();

		void place_structure(std::size_t, std::size_t, std::size_t);
		void set_resident(std::size_t, std::size_t);
		std::size_t get_resident(std::size_t) const;
		void add_residences(std::size_t, const std::vector<std::size_t>&);
		void add_residence(std::size_t, std::size_t);

		void set_radius(std::size_t, std::size_t);
	private:
		bool in_board_(std::size_t) const;
		void link_(std::size_t, std::vector<GridNodeComponent*>&);
		std::size_t abs_(int) const;

		EntitySystem& entities_;
		Ogre::SceneManager& scene_mgr_;

		std::size_t width_, height_;
		Ogre::Vector2 start_;
		Ogre::Real distance_;
		std::vector<std::size_t> board_;

		bool graphics_loaded_, graph_visible_;
		std::string error_blueprint;
};