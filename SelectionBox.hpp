#pragma once

#include <Ogre.h>

#include <vector>

class SelectionBox : public Ogre::ManualObject
{
	public:
	private:
		/**
		 * Currently selected entities.
		 */
		std::vector<Ogre::SceneNode*> selected_entities_;

};