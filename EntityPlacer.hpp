#pragma once

#include <Ogre.h>

#include <string>

#include "EntitySystem.hpp"
#include "Console.hpp"
#include "GridSystem.hpp"

/**
 * Class allowing the player/developer to place entities on the ground.
 * (Mainly used by the EntityCreator class, but can be invoked by
 * "game.place_entity(TABLE)" where TABLE is the name of the desired entity's
 * blueprint)
 */
class EntityPlacer
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's entity system.
		 * Param: Reference to the game's grid system, used for node snapping when
		 *        placing structures (i.e. walls, buildings...).
		 */
		EntityPlacer(EntitySystem&, GridSystem&);

		/**
		 * Destructor.
		 */
		~EntityPlacer();

		/**
		 * Brief: Checks if a given entity blueprint contains a graphics component and if so,
		 *        sets it as the currently placed entity by creating a dummy entity following
		 *        the cursor.
		 * Param: Name of the blueprint table (describing the placed entity).
		 */
		void set_current_entity_table(const std::string&);

		/**
		 * Brief: Called every frame when the entity placer is active, adjusts the dummy entity's
		 *        position to the cursor's.
		 * Param: Position of the mouse cursor (recieved from Game::get_mouse_click_position).
		 */
		void update_position(const Ogre::Vector3&);

		/**
		 * Brief: Creates a new entity from the blueprint table at the mouse cursor's current
		 *        position and informs the developer in the developer console.
		 * Param: Reference to the game's console.
		 */
		std::size_t place(Console& console);

		/**
		 * Brief: Sets the visibility status of the placer (and it's dummy entity).
		 * Param: The new visibility status.
		 */
		void set_visible(bool);

		/**
		 * Brief: Returns true if the placer is currently active (and thus the dummy entity visible),
		 *        false otherwise.
		 */
		bool is_visible() const;
	private:
		/**
		 * Reference to the game's entity system.
		 * (Used to create entities as well as checking the loaded tables.)
		 */
		EntitySystem& entities_;

		/**
		 * Reference to the game's grid system.
		 * (Used for node snapping when placing structures).
		 */
		GridSystem& grid_;

		/**
		 * Current position of the dummy entity (used to avoid the need
		 * to pass the position again on the actual placement cal).
		 */
		Ogre::Vector3 curr_position_;

		/**
		 * Pointer to the scene node the dummy entity is attached to.
		 */
		Ogre::SceneNode* placing_node_;

		/**
		 * The placer's visibility (and active) status.
		 */
		bool visible_;

		/**
		 * Name of the blueprint of the currently placed entity.
		 */
		std::string table_name_;

		/**
		 * Used to correctly place the newly created entity on the ground.
		 * (The mouse cursor position is at 0 Y coordinate, but the entity might
		 * need to be higher due to it's central point not being at the bottom
		 * of the model.)
		 */
		Ogre::Real half_height_;

		/**
		 * Determines if a structure (wall, building etc.) is being placed, this will
		 * make the dummy entity to snap to the grid nodes.
		 */
		bool placing_structure_;

		/**
		 * Radius of the placed structure (if it's covering more than one node).
		 */
		std::size_t structure_radius_;

		/**
		 * ID of the dummy entity, used to destroy the entity once the visibility status
		 * is changed to false to avoid placement when the game is saved.
		 * TODO: What about when the dummy entity is visible?
		 */
		std::size_t placed_id_;
};