#pragma once

#include "System.hpp"
#include "Typedefs.hpp"
class EntitySystem;

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
		~AISystem() = default;

		/**
		 * Brief: Updates all valid entities by calling their update function stored in the
		 *        AIComponent::blueprint table.
		 * Param: Time since the last frame.
		 */
		void update(tdt::real) override;

		/**
		 * Brief: Sets the amount of seconds it takes before the next AI
		 *        update will be performed.
		 * Param: Update period time (in seconds).
		 */
		void set_update_period(tdt::real);
		
		/**
		 * Brief: Returns the amount of seconds it takes before the next AI
		 *        update will be performed.
		 */
		tdt::real get_update_period() const;

		/**
		 * Brief: Sets the update timer equal to the period and thus forcing
		 *        all entities' AI to be updated on next AISystem::update call.
		 */
		void force_update();

	private:
		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;

		/**
		 * Used to track the time and check if the entities should be updated.
		 */
		tdt::real update_timer_, update_period_;
};