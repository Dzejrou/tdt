#pragma once

#include <Ogre.h>

#include <vector>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "Line.hpp"

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
		std::size_t get_node_from_id(std::size_t, std::size_t) const;
		std::size_t get_node_from_position(Ogre::Real, Ogre::Real) const;
	private:
		EntitySystem& entities_;
		Ogre::SceneManager& scene_mgr_;

		std::size_t width_, height_;
		std::vector<std::size_t> board_;
};