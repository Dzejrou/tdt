#pragma once

#include "System.hpp"
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Handles triggers by checking if an entity is standing in their
 * radius when they are off cooldowns.
 */
class TriggerSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Entity system containing entities this system
		 *        works with.
		 */
		TriggerSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~TriggerSystem() = default;

		/**
		 * Brief: Checks if any entities have been triggered and performs
		 *        their associated actions if they were.
		 * Param: Time since the last frame.
		 */
		void update(tdt::real) override;

		/**
		 * Brief: Sets the time period between trigger checks.
		 * Param: The new time period.
		 */
		void set_check_period(tdt::real);

		/**
		 * Brief: Returns the time period between trigger checks.
		 */
		tdt::real get_check_period() const;

	private:
		/**
		 * Entity system containing the entities this system works with.
		 */
		EntitySystem& entities_;

		/**
		 * Allow for dynamic time periods between trigger checks.
		 */
		tdt::real check_timer_, check_period_;
};