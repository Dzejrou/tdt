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
		 * Brief: Returns true if a given entity is valid and can be updated by this system, should be tested
		 *        before the AISystem::update call.
		 * Param: ID of the entity.
		 */
		bool is_valid(std::size_t) const;

		/**
		 * Brief: Returns true if two given entities are friendly (i.e. either one of them is neutral
		 *        or they have the same FACTION alegiance), false otherwise.
		 * Param: ID of the first entity.
		 * Param: ID of the second entity.
		 */
		bool is_friendly(std::size_t, std::size_t) const;

		/**
		 * Brief: Returns true if a given entity is neutral, returns false otherwise.
		 * Param: ID of the entity.
		 */
		bool is_neutral(std::size_t) const;

		/**
		 * Brief: Returns true if a given entity is inanimate (i.e. does not have an AIComponent),
		 *        false otherwise.
		 * Param: ID of the entity.
		 */
		bool is_inanimate(std::size_t) const;

		/**
		 * Brief: Returns name of the blueprint table of a given entity (i.e. the table containing
		 *        it's init, update and finnish methods).
		 * Param: ID of the entity.
		 */
		std::string get_blueprint(std::size_t) const;

		/**
		 * Brief: Changes the blueprint table name of a given entity.
		 * Param: ID of the entity.
		 * Param: Name of the new blueprint table.
		 */
		void set_blueprint(std::size_t, const std::string&);

		/**
		 * Brief: Returns the state a given entity is in.
		 * Param: ID of the entity.
		 */
		ENTITY_STATE get_state(std::size_t) const;

		/**
		 * Brief: Changes the state of a given entity.
		 * Param: ID of the entity.
		 * Param: New state.
		 */
		void set_state(std::size_t, ENTITY_STATE);

		/**
		 * Brief: Returns the FACTION of a given entity.
		 * Param: ID of the entity.
		 */
		FACTION get_faction(std::size_t) const;

		/**
		 * Brief: Changes the FACTION of a given entity.
		 * Param: ID of the entity.
		 * Param: New FACTION.
		 */
		void set_faction(std::size_t, FACTION);

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