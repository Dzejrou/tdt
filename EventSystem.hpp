#pragma once

#include <Ogre.h>
#include <cstdlib>
#include "System.hpp"
#include "EntitySystem.hpp"
#include "Helpers.hpp"

class EventSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Entity system that has entities this system will manage.
		 */
		EventSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~EventSystem() {}

		/**
		 * Brief: Checks for handlers of all active events and if needed, handles
		 *        them.
		 * Param: Time since last frame.
		 */
		void update(Ogre::Real) override;

		/**
		 * Brief: Sets the time it takes before an update is performed
		 *        (in seconds).
		 * Param: The new update time period.
		 */
		void set_update_period(Ogre::Real);

		/**
		 * Brief: Returns the time it takes before an update is performed
		 *        (in seconds).
		 */
		Ogre::Real get_update_period() const;

		/**
		 * Brief: Sets the value by which the frame time is multiplied before
		 *        it's added to the update timer.
		 * Param: The new multiplier value.
		 */
		void set_update_time_multiplier(Ogre::Real);

		/**
		 * Brief: Returns the value by which the frame time is multiplied before
		 *        it's added to the update timer.
		 */
		Ogre::Real get_update_time_multiplier() const;
	private:
		/**
		 * Brief: Handles a given event by a given entity that can handle it, returns
		 *        true if the event will be destroyed after this call (single handler event),
		 *        false if the event persist (multi handler event).
		 * Param: ID of the handler.
		 * Param: ID of the event.
		 */
		bool handle_event_(std::size_t, std::size_t);

		/**
		 * Entity system that has entities this system will manage.
		 */
		EntitySystem& entities_;

		/**
		 * Allow for less frequent updates, since per frame updates are quite
		 * unnecessary and resource wasting.
		 */
		Ogre::Real update_period_, curr_update_time_;
		
		/**
		 * Allows to speed up/slow down the update timer.
		 */
		Ogre::Real update_time_multiplier_;
};