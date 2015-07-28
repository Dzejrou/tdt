#pragma once

#include <Ogre.h>

#include <vector>
#include <array>
#include <tuple>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "Line.hpp"

/**
 *
 */
class GridSystem : public System
{
	public:
		GridSystem(EntitySystem&, Ogre::SceneManager&);
		~GridSystem() {}

		void update(Ogre::Real);
		bool is_valid(std::size_t) const;

		std::size_t add_node(Ogre::Real, Ogre::Real, Ogre::Real);
		std::size_t add_line(std::size_t, std::size_t);
		void create_graph(std::size_t, std::size_t, Ogre::Real, Ogre::Real, Ogre::Real);
		std::size_t get_node(std::size_t, std::size_t) const;
		std::size_t get_node_from_position(Ogre::Real, Ogre::Real) const;
		void create_graphics();
		void delete_graphics();
		void set_visible(bool);
		bool is_visible() const;

		std::array<std::size_t, 4> get_neighbours(std::size_t) const;
		bool is_free(std::size_t) const;
		void set_free(std::size_t, bool);

		std::size_t get_manhattan_distance(std::size_t, std::size_t) const;

		void perform_a_star(std::size_t, std::size_t, std::size_t);

		const std::string& get_pathpfinding_blueprint(std::size_t) const;
		void set_pathfinding_blueprint(std::size_t, const std::string&);
		int get_cost(std::size_t, std::size_t) const;
	private:
		std::tuple<std::size_t, std::size_t> get_board_coords_(std::size_t) const;

		EntitySystem& entities_;
		Ogre::SceneManager& scene_mgr_;

		std::size_t width_, height_;
		Ogre::Vector2 start_;
		Ogre::Real distance_;
		std::vector<std::size_t> board_;

		bool graphics_loaded_, graph_visible_;
};