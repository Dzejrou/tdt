#pragma once

#include <Ogre.h>
#include "System.hpp"
#include "EntitySystem.hpp"
#include "Helpers.hpp"

class TimeSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's entity system.
		 */
		TimeSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~TimeSystem() {}

		/**
		 * Brief: Updates the time passed for all TimeComponents and handles
		 *        those that surpassed their target time.
		 * Param: Time since last frame.
		 */
		void update(Ogre::Real) override;

		/**
		 * Brief: Adds a given time value to all TimeComponents.
		 * Param: Time to add.
		 */
		void advance_all_timers(Ogre::Real);
	private:
		/**
		 * Brief: Handles a time event when it's timer finnishes.
		 * Param: ID of the time event.
		 * Param: Reference to the TimeComponent of this time event.
		 */
		void handle_event_(std::size_t, TimeComponent&);

		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;
};