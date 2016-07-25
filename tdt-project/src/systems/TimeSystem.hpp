#pragma once

#include <Enums.hpp>
#include <Typedefs.hpp>
#include "System.hpp"
class EntitySystem;
struct TimeComponent;

class TimeSystem : public System
{
	public:
		/**
		 * Constructor.
		 * \param Reference to the game's entity system.
		 */
		TimeSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~TimeSystem() = default;

		/**
		 * \brief Updates the time passed for all TimeComponents and handles
		 *        those that surpassed their target time.
		 * \param Time since last frame.
		 */
		void update(tdt::real) override;

		/**
		 * \brief Adds a given time value to all TimeComponents.
		 * \param Time to add.
		 */
		void advance_all_timers(tdt::real);

		/**
		 * \brief Adds a given time value to all TimeComponents that match
		 *        the given time event type.
		 * \param Time to add.
		 * \param Time even type to match.
		 */
		void advance_all_timers_of_type(tdt::real, TIME_EVENT);

		/**
		 * \brief Sets the time value by which are all frame times multiplied
		 *        when added to timers (this allows to slow/speed up all timers).
		 * \param The new time multiplier.
		 */
		void set_time_multiplier(tdt::real = 1.f);

		/**
		 * \brief Returns the time value by which are all frame times multiplied
		 *        when added to timers.
		 */
		tdt::real get_time_multiplier();

	private:
		/**
		 * \brief Handles a time event when it's timer finnishes.
		 * \param ID of the time event.
		 * \param Reference to the TimeComponent of this time event.
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