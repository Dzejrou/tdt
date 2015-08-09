#pragma once

#include <Ogre.h>

#include <string>

#include "EntitySystem.hpp"
#include "Console.hpp"
#include "GridSystem.hpp"

class EntityPlacer
{
	public:
		EntityPlacer(EntitySystem&, GridSystem&);
		~EntityPlacer();

		void set_current_entity_table(const std::string&);
		void update_position(const Ogre::Vector3&);
		std::size_t place(Console& console);
		void set_visible(bool);
		bool is_visible() const;
	private:
		EntitySystem& entities_;
		GridSystem& grid_;
		Ogre::Vector3 curr_position_;
		Ogre::SceneNode* placing_node_;
		bool visible_;
		std::string table_name_;
		Ogre::Real half_height_;
		bool placing_structure_;
		std::size_t structure_radius_;
		std::size_t placed_id_;
};