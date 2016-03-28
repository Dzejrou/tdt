#pragma once

#include "System.hpp"
#include "Typedefs.hpp"
class EntitySystem;

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
		~EventSystem() = default;

		/**
		 * Brief: Checks for handlers of all active events and if needed, handles
		 *        them.
		 * Param: Time since last frame.
		 */
		void update(tdt::real) override;

		/**
		 * Brief: Sets the time it takes before an update is performed
		 *        (in seconds).
		 * Param: The new update time period.
		 */
		void set_update_period(tdt::real);

		/**
		 * Brief: Returns the time it takes before an update is performed
		 *        (in seconds).
		 */
		tdt::real get_update_period() const;

		/**
		 * Brief: Sets the value by which the frame time is multiplied before
		 *        it's added to the update timer.
		 * Param: The new multiplier value.
		 */
		void set_update_time_multiplier(tdt::real);

		/**
		 * Brief: Returns the value by which the frame time is multiplied before
		 *        it's added to the update timer.
		 */
		tdt::real get_update_time_multiplier() const;

	private:
		/**
		 * Brief: Handles a given event by a given entity that can handle it, returns
		 *        true if the event will be destroyed after this call (single handler event),
		 *        false if the event persist (multi handler event).
		 * Param: ID of the handler.
		 * Param: ID of the event.
		 */
		bool handle_event_(tdt::uint, tdt::uint);

		/**
		 * Entity system that has entities this system will manage.
		 */
		EntitySystem& entities_;

		/**
		 * Allow for less frequent updates, since per frame updates are quite
		 * unnecessary and resource wasting.
		 */
		tdt::real update_period_, curr_update_time_;
		
		/**
		 * Allows to speed up/slow down the update timer.
		 */
		tdt::real update_time_multiplier_;
};