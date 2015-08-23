#pragma once

#include <Ogre.h>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "HealthHelper.hpp"

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
		~HealthSystem() override {}

		/**
		 * Brief: Updates a the system by checking every valid entity's health (or death) status
		 *        and applying health regeneration if necessary.
		 * Param: Time since the last frame.
		 */
		void update(Ogre::Real) override;

		/**
		 * Brief: Adds one to the regeneration timer, simulating continuous regeration, should
		 *        be called once per frame before the update method.
		 * Param: Time since the last frame.
		 */
		void update_regen(Ogre::Real);

		/**
		 * Brief: Sets the amount of time it takes for one regeneration
		 *        tick to happen (in seconds).
		 * Param: The new regen period.
		 */

		/**
		 */
	public:
		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;
		
		/**
		 * Amount of frames since the last regeneration tick.
		 */
		Ogre::Real regen_timer_;

		/**
		 * Amount of frames per regeneration period.
		 */
		Ogre::Real regen_period_;

		/**
		 * True if this frame's update should renerate health.
		 */
		bool regen_;
};