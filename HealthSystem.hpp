#pragma once

#include <Ogre.h>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

/**
 * System that manages the regeneration and health of entities
 * on each frame.
 */
class HealthSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's entity system.
		 */
		HealthSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~HealthSystem() {}

		/**
		 * Brief: Updates a single valid entity by checking it's health (or death) status
		 *        and applying health regeneration if necessary.
		 * Param: ID of the entity.
		 * Param: Time since the last frame.
		 */
		void update(std::size_t, Ogre::Real);

		/**
		 * Brief: Returns true if an entity is valid, false otherwise. (Should be tested before
		 *        the update call.)
		 * Param: ID of the entity.
		 */
		bool is_valid(std::size_t) const;

		/**
		 * Brief: Adds one to the regeneration timer, simulating continuous regeration, should
		 *        be called once per frame before the update method.
		 */
		void update_regen();

		/**
		 * Brief: Returns the current health amount of a given entity.
		 * Param: ID of the entity.
		 */
		std::size_t get_health(std::size_t) const;

		/**
		 * Brief: Increases the current health amount of an entity by a given amount
		 *        up to the maximum value stored in it's HealthComponent.
		 * Param: ID of the entity.
		 * Param: Amount of health to be added.
		 * Node: To increase health along with the maximum value, see HealthSystem::buff.
		 */
		void add_health(std::size_t, std::size_t);

		/**
		 * Brief: Subtracts a given amount from the current health of an entity, taking
		 *        it's defense into account by default.
		 * Param: ID of the entity.
		 * Param: Amount of health to be subtracted.
		 * Param: Optional boolean indicator, if true, the entity's defense will be ignored,
		 *        otherwise it will be subtracted from the given amount.
		 */
		void sub_health(std::size_t, std::size_t, bool = false);

		/**
		 * Brief: Sets the current health amount of an entity to it's maximum value.
		 * Param: ID of the entity.
		 */
		void heal(std::size_t);

		/**
		 * Brief: Increases the current and maximum health amount of an entity by a given value.
		 * Param: ID of the entity.
		 * Param: Amount of health to be added.
		 */
		void buff(std::size_t, std::size_t);

		/**
		 * Brief: Returns the defense of a given entity.
		 * Param: ID of the entity.
		 */
		std::size_t get_defense(std::size_t) const;

		/**
		 * Brief: Increases the defense of an entity by a given amount.
		 * Param: ID of the entity.
		 * Param: Amount of defense to be added.
		 */
		void add_defense(std::size_t, std::size_t);

		/**
		 * Brief: Reduces the defense of an entity by a given amount.
		 * Param: ID of the entity.
		 * Param: Amounf of defense to be removed.
		 */
		void sub_defense(std::size_t, std::size_t);
	public:
		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;
		
		/**
		 * Amount of frames since the last regeneration tick.
		 */
		std::size_t regen_timer_;

		/**
		 * Amount of frames per regeneration period.
		 */
		std::size_t regen_period_;

		/**
		 * True if this frame's update should renerate health.
		 */
		bool regen_;
};