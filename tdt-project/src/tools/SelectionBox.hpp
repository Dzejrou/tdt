#pragma once

#include <OGRE/Ogre.h>
#include <vector>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Class representing the ingame selection box (created by moving the left mouse while
 * pressing the left mouse button) to select multiple entities on screen or a single entity
 * (by simply clicking).
 */
class SelectionBox : public Ogre::ManualObject
{
	public:
		/**
		 * Constructor.
		 * \param Name of this object (passed to ManualObject constructor - hence the type).
		 * \param Reference to a volume query used for multi selection.
		 * \param Reference to a ray query used for single selection.
		 * \param Reference to the game's main scene manager.
		 */
		SelectionBox(const Ogre::String&, EntitySystem&,
					 Ogre::PlaneBoundedVolumeListSceneQuery&,
					 Ogre::RaySceneQuery&, Ogre::SceneManager&);

		/**
		 * Destructor.
		 * \note Even thous the queries are captured by reference, they need to be destroyed manually
		 *       using the scene manager.
		 */
		~SelectionBox();

		/**
		 * \brief Recreates the selection box with the given coordinates.
		 * \param Left side coordinate.
		 * \param Top side coordinate.
		 * \param Right side coordinate.
		 * \param Bottom axis coordinate.
		 */
		void set_corners(tdt::real, tdt::real, tdt::real, tdt::real);

		/**
		 * \brief Overload of the SelectionBox::set_corners(float, float, float, float) method
		 *        used as a simple interface when using vectors.
		 * \param Coordinate of the top left corner.
		 * \param Coordinate of the bottom right corner.
		 */
		void set_corners(const Ogre::Vector2&, const Ogre::Vector2&);

		/**
		 * \brief Returns (by reference) a vector containing ID's of all currently selected entities.
		 */
		std::vector<tdt::uint>& get_selected_entities();

		/**
		 * \brief Adds a given object to the vector of selected entities.
		 * \param Reference to the object from which the entity ID will be deduced.
		 */
		void select_object(Ogre::MovableObject&);

		/**
		 * \brief Deselects all currently selected entities.
		 */
		void clear_selected_entities();

		/**
		 * \brief Performs the selection, to be called when the mouse is released.
		 * \param Coordinate of the end point of the box (mouse position).
		 * \param Reference to the camera the query should be performed from.
		 * \param True if the the new selection should be appended to the current selection.
		 * \note The starting point has to be saved prior to this call (i.e. when the
		 *       mouse button gets pressed) in order for the selection to work
		 *       properly.
		 */
		void execute_selection(const Ogre::Vector2&, Ogre::Camera&, bool = false);

		/**
		 * \brief Sets the starting point of the current selection, should be
		 *        called upon the initial mouse button click.
		 * \param Coordinate of the starting point.
		 */
		void set_starting_point(const Ogre::Vector2&);

		/**
		 * \brief Sets the selecting mode (and the visibility flag of the selection box).
		 * \param Bool value representing the new visibility mode.
		 */
		void set_selecting(bool);

		/**
		 * \brief Returns true if the selection box is currently selecting.
		 */
		bool is_selecting() const;

		/**
		 * \brief Extends the selection box to a given coordinate, using the start_ coordinate
		 *        provided by SelectionBox::set_starting_point as the initial point.
		 * \param Coordinate of the ending point.
		 */
		void extend_to(const Ogre::Vector2&);
	private:
		/**
		 * \brief Used within the SelectionBox::execute_selection method when the selection
		 *        box is two small (i.e. a single click) and performs a ray query selecting
		 *        a single closest entity under the player's cursor.
		 * \param Reference to the game's main camera.
		 */
		void execute_single_selection(Ogre::Camera&);

		/**
		 * Currently selected entities.
		 */
		std::vector<tdt::uint> selected_entities_;

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
		 * Reference to the game's main scene manager.
		 */
		Ogre::SceneManager& scene_mgr_;
};