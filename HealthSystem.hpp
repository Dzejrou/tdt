#pragma once

#include "System.hpp"
#include "Typedefs.hpp"
class EntitySystem;

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
		~HealthSystem() = default;

		/**
		 * Brief: Updates a the system by checking every valid entity's health (or death) status
		 *        and applying health regeneration if necessary.
		 * Param: Time since the last frame.
		 */
		void update(tdt::real) override;

		/**
		 * Brief: Adds one to the regeneration timer, simulating continuous regeration, should
		 *        be called once per frame before the update method.
		 * Param: Time since the last frame.
		 */
		void update_regen(tdt::real);

		/**
		 * Brief: Sets the amount of time it takes for one regeneration
		 *        tick to happen (in seconds).
		 * Param: The new regen period.
		 */
		void set_regen_period(tdt::real);

		/**
		 * Brief: Returns the amount of time it takes for one regeneration
		 *        tick to happen (in seconds).
		 */
		tdt::real get_regen_period() const;

	private:
		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;
		
		/**
		 * Amount of frames since the last regeneration tick.
		 */
		tdt::real regen_timer_;

		/**
		 * Amount of frames per regeneration period.
		 */
		tdt::real regen_period_;

		/**
		 * True if this frame's update should renerate health.
		 */
		bool regen_;
};