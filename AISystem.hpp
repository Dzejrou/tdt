#pragma once

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "lppscript\LppScript.hpp"

/**
 * System handling the AI of entities by calling their update method every frame.
 */
class AISystem : public System
{
	public:
		/**
	     * Constructor.
		 * Param: Reference to the game's entity system.
		 */
		AISystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~AISystem() {}

		/**
		 * Brief: Updates all valid entities by calling their update function stored in the
		 *        AIComponent::blueprint table.
		 * Param: Time since the last frame.
		 */
		void update(Ogre::Real);

		/**
		 * Brief: Returns true if two given entities are friendly (i.e. either one of them is neutral
		 *        or they have the same FACTION alegiance), false otherwise.
		 * Param: ID of the first entity.
		 * Param: ID of the second entity.
		 */
		bool is_friendly(std::size_t, std::size_t) const; // TODO: In Lua.

		/**
		 * Brief: Returns true if a given entity is neutral, returns false otherwise.
		 * Param: ID of the entity.
		 */
		bool is_neutral(std::size_t) const; // TODO: In Lua.

		/**
		 * Brief: Returns true if a given entity is inanimate (i.e. does not have an AIComponent),
		 *        false otherwise.
		 * Param: ID of the entity.
		 */
		bool is_inanimate(std::size_t) const; // TODO: In Lua.

		/**
		 * Brief: Sets the amount of seconds it takes before the next AI
		 *        update will be performed.
		 * Param: Update period time (in seconds).
		 */
		void set_update_period(Ogre::Real);
		
		/**
		 * Brief: Returns the amount of seconds it takes before the next AI
		 *        update will be performed.
		 */
		Ogre::Real get_update_period() const;

		/**
		 */
	private:
		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;

		/**
		 * Used to track the time and check if the entities should be updated.
		 * TODO: Add as a setting to a config (along with regen timer etc).
		 */
		Ogre::Real update_timer_, update_period_;
};