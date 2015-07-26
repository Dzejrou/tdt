#pragma once

#include <Ogre.h>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

class GridSystem : public System
{
	public:
		GridSystem(EntitySystem&, Ogre::SceneManager&);
		~GridSystem() {}

		void update(Ogre::Real);
		bool is_valid(std::size_t) const;

		std::size_t add_node(Ogre::Real, Ogre::Real);
		std::size_t add_line(std::size_t, std::size_t);
	private:

		EntitySystem& entities_;
		Ogre::SceneManager& scene_mgr_;
};