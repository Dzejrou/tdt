#pragma once

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "lppscript\LppScript.hpp"

/**
 *
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
		 * Brief: Updates a given valid entity by calling the update function stored in the
		 *        AIComponent::blueprint table.
		 * Param: ID of the entity.
		 * Param: Time since the last frame.
		 */
		void update(std::size_t, Ogre::Real);

		/**
		 * Brief: Returns true if a given entity is valid and can be updated by this system, should be tested
		 *        before the AISystem::update call.
		 * Param: ID of the entity.
		 */
		bool is_valid(std::size_t) const;

		/**
		 * Brief: Returns true if two given entities are friendly (i.e. either one of them is neutral
		 *        or they have the same faction alegiance), false otherwise.
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
		 * Brief: Returns the state a given entity is in.
		 * Param: ID of the entity.
		 */
		EntityState get_state(std::size_t) const;

		/**
		 * Brief: Returns the faction of a given entity.
		 * Param: ID of the entity.
		 */
		Faction get_faction(std::size_t) const;

	private:
		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;
};