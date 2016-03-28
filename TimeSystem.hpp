#pragma once

#include "Enums.hpp"
#include "System.hpp"
#include "Typedefs.hpp"
class EntitySystem;
struct TimeComponent;

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
		~TimeSystem() = default;

		/**
		 * Brief: Updates the time passed for all TimeComponents and handles
		 *        those that surpassed their target time.
		 * Param: Time since last frame.
		 */
		void update(tdt::real) override;

		/**
		 * Brief: Adds a given time value to all TimeComponents.
		 * Param: Time to add.
		 */
		void advance_all_timers(tdt::real);

		/**
		 * Brief: Adds a given time value to all TimeComponents that match
		 *        the given time event type.
		 * Param: Time to add.
		 * Param: Time even type to match.
		 */
		void advance_all_timers_of_type(tdt::real, TIME_EVENT);

		/**
		 * Brief: Sets the time value by which are all frame times multiplied
		 *        when added to timers (this allows to slow/speed up all timers).
		 * Param: The new time multiplier.
		 */
		void set_time_multiplier(tdt::real = 1.f);

		/**
		 * Brief: Returns the time value by which are all frame times multiplied
		 *        when added to timers.
		 */
		tdt::real get_time_multiplier();

	private:
		/**
		 * Brief: Handles a time event when it's timer finnishes.
		 * Param: ID of the time event.
		 * Param: Reference to the TimeComponent of this time event.
		 */
		void handle_event_(tdt::uint, TimeComponent&);

		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;

		/**
		 * Allows to speed up all timers.
		 */
		tdt::real time_multiplier_;
};