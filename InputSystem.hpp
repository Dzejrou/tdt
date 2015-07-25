#pragma once

#include <Ogre.h>
#include <OIS.h>
#include <stdexcept>
#include <memory>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

/**
 * System handling entities controlled by the player's keyboard input and changing
 * the game's view mode (between 1st and 3rd person).
 */
class InputSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's EntitySystem instance.
		 * Param: Reference to the keyboard being used.
		 * Param: Reference to the camera for it's manipulation during the 1st person mode.
		 */
		InputSystem(EntitySystem&, OIS::Keyboard&, Ogre::Camera&);

		/**
		 * Destructor.
		 */
		~InputSystem() {}

		/**
		 * Brief: Handles the input for the entity that is
		 *        currently in the first person mode.
		 * Param: Time since the last frame.
		 */
		void update(Ogre::Real);

		/**
		 * Brief: Returns true if an entity is valid and thus can be updated by this system, should be used
		 *        to test validity before the InputSystem::update call.
		 * Param: ID of the entity.
		 */
		bool is_valid(std::size_t) const;

		/**
		 * Brief: Returns true if the game is in the first person mode, returns
		 *        false otherwise.
		 */
		bool is_first_person() const;

		/**
		 * Brief: Changes the first person mode status for an entity and also loads an InputComponent for it
		 *        if it does not have it but has an AIComponent holding information about it's input_handler method.
		 *        (Backups the AIComponent in such cases and restores it when the entity leaves first person mode.)
		 */
		void set_first_person(bool, std::size_t = 0);

		/**
		 * Brief: Rebinds a given key with an OIS key number. Use OIS::KC_W, OIS::KC_S, OIS::KC_A and OIS::KC_D
		 *        to determine which key should be rebinded.
		 * Param: Key to be rebinded.
		 * Param: The new key.
		 */
		void rebind(int, int);

		/**
		 * Brief: Changes an entity's input handler.
		 * Param: Name of the new input handler (Lua function).
		 * Note: The handler recieves the ID of the entity and the key number when it's called, for current
		 *       keybindings use the game.enum.input Lua table.
		 */
		void set_input_handler(std::size_t, const std::string&);
	private:
		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;

		/**
		 * Determines if the first person view is turned on.
		 */
		bool first_person_;

		/**
		 * If the first person view is turned on, this holds ID of the entity being controlled.
		 */
		std::size_t first_person_id_;

		/**
		 * Reference to the keyboard being used.
		 */
		OIS::Keyboard& keyboard_;

		/**
		 * Current keybindings, allow rebinding.
		 */
		int KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT;

		/**
		 * Reference to the game's main camera.
		 */
		Ogre::Camera& cam_;

		/**
		 * Backup of the camera info for easy restoring once
		 * the game leaves the first person view.
		 */
		Ogre::Vector3 cam_position_;
		Ogre::Quaternion cam_orientation_;
		
		/**
		 * Backup of the AI component when entering first person view.
		 */
		std::unique_ptr<AIComponent> ai_backup_;

		/**
		 * Determines if the InputComponent of the entity being controlled in the
		 * first person view should be deleted once the game changes back to third person view.
		 */
		bool delete_input_;
};