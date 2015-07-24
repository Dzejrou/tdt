#pragma once

#include <Ogre.h>

#include <vector>

#include "EntitySystem.hpp"

/**
 *
 */
class SelectionBox : public Ogre::ManualObject
{
	public:
		SelectionBox(const Ogre::String&, EntitySystem&);
		~SelectionBox() {}

		void set_corners(float, float, float, float);
		void set_corners(const Ogre::Vector2&, const Ogre::Vector2&);
		std::vector<std::size_t>& get_selected_entities();
		void select_object(Ogre::MovableObject*);
		void clear_selected_entities();
		void execute_selection();
	private:
		/**
		 * Currently selected entities.
		 */
		std::vector<std::size_t> selected_entities_;

		/**
		 * Reference to the game's entity system, used to identify an entity ID
		 * from an entity SceneNode.
		 */
		EntitySystem& entities_;

};