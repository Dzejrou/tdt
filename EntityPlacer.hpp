#pragma once

#include <Ogre.h>
#include <string>
#include "EntitySystem.hpp"
#include "GridSystem.hpp"
#include "Helpers.hpp"

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
		 * Param: Scene manager that will hold the dummy node.
		 */
		EntityPlacer(EntitySystem&, GridSystem&, Ogre::SceneManager&);

		/**
		 * Destructor.
		 */
		~EntityPlacer();

		/**
		 * Brief: Checks if a given entity blueprint contains a graphics component and if so,
		 *        sets it as the currently placed entity by creating a dummy entity following
		 *        the cursor.
		 * Param: Name of the blueprint table (describing the placed entity).
		 * Param: If true, the cost of the entity will be subtracted from the player's gold
		 *        and the entity won't be placed if the player does not have sufficient funds.
		 */
		void set_current_entity_table(const std::string&, bool = false);

		/**
		 * Brief: Called every frame when the entity placer is active, adjusts the dummy entity's
		 *        position to the cursor's.
		 * Param: Position of the mouse cursor (recieved from Game::get_mouse_click_position).
		 */
		void update_position(const Ogre::Vector3&);

		/**
		 * Brief: Creates a new entity from the blueprint table at the mouse cursor's current
		 *        position and informs the developer in the developer console.
		 */
		std::size_t place();

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

		/**
		 * Brief: Toggles (=negates) the flag for entity placing while the game is paused.
		 */
		void toggle_placing_when_game_paused();

		/**
		 * Brief: Returns true if the placer can place entities when the game is paused,
		 *        false otherwise.
		 */
		bool can_place_when_game_paused() const;
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
		 * Scene manager used to hold the dummy node and manipulate models.
		 */
		Ogre::SceneManager& mgr_;

		/**
		 * Entity representing the mesh of the placed object.
		 */
		Ogre::Entity* ent_;

		/**
		 * Price of the currently placed entity.
		 */
		std::size_t price_;

		/**
		 * Used for debugging, allows to place spawners when the game is paused and
		 * this their production is halted.
		 */
		bool can_place_when_game_paused_{false};
};