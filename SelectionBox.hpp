#pragma once

#include <Ogre.h>

#include <vector>

#include "EntitySystem.hpp"

class SelectionBox : public Ogre::ManualObject
{
	public:
		SelectionBox(const Ogre::String&, EntitySystem&);
		~SelectionBox() {}

		void set_corners(float, float, float, float);
		void set_corners(const Ogre::Vector2&, const Ogre::Vector2&);
		std::vector<std::size_t>& get_selected_entities();
		void select_object(Ogre::MovableObject*);
	private:
		/**
		 * Currently selected entities.
		 */
		std::vector<std::size_t> selected_entities_;

		/**
		 *
		 */
		EntitySystem& entities_;

};