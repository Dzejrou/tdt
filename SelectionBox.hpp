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
		SelectionBox(const Ogre::String&, EntitySystem&,
					 Ogre::PlaneBoundedVolumeListSceneQuery&,
					 Ogre::RaySceneQuery&, Ogre::SceneManager&);
		~SelectionBox();

		void set_corners(float, float, float, float);
		void set_corners(const Ogre::Vector2&, const Ogre::Vector2&);
		std::vector<std::size_t>& get_selected_entities();
		void select_object(Ogre::MovableObject&);
		void clear_selected_entities();
		void execute_selection(const Ogre::Vector2&, Ogre::Camera&);
		void set_starting_point(const Ogre::Vector2&);
		void set_selecting(bool);
		bool is_selecting() const;
		void extend_to(const Ogre::Vector2&);
		void execute_single_selection(Ogre::Camera&);
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

		/**
		 * Vector containing the coordinates of the starting point of the selection.
		 * (Ending point will be specified in the SelectionBox::execute_selection method.)
		 */
		Ogre::Vector2 start_;

		/**
		 * Scene query used to find all the entities that are within the selection box.
		 */
		Ogre::PlaneBoundedVolumeListSceneQuery& volume_query_;

		/**
		 * Scene query used to find an entity when the selection box is too small.
		 */
		Ogre::RaySceneQuery& ray_query_;

		/**
		 * Determines if the player is currently selecting entities.
		 */
		bool selection_in_progress_;

		/**
		 *
		 */
		Ogre::SceneManager& scene_mgr_;
};