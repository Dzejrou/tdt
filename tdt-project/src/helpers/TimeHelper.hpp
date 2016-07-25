#pragma once

#include <Enums.hpp>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of the
 * time component.
 */
namespace TimeHelper
{
	/**
	 * \brief Returns the time that has passed since the timer started.
	 * \param Entity system which contains the timer.
	 * \param ID of th entity.
	 */
	tdt::real get_curr_time(EntitySystem&, tdt::uint);

	/**
	 * \brief Adds a given time value to a given timer.
	 * \param Entity system which contains the timer.
	 * \param ID of the timer.
	 * \param Time to add.
	 */
	void advance_curr_time(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Completes a given timer (by maxing it's current time).
	 * \param Entity system which contains the timer.
	 * \param ID of the timer.
	 */
	void max_curr_time(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the time a given timer requires for completion.
	 * \param Entity system which contains the timer.
	 * \param ID of the timer.
	 * \param The new time limit.
	 */
	void set_time_limit(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the time a given timer requires for completion.
	 * \param Entity system which contains the timer.
	 * \param ID of the timer.
	 */
	tdt::real get_time_limit(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the ID of the event a given timer starts/ends.
	 * \param Entity system which contains the timer.
	 * \param ID of the timer.
	 * \param ID of the event.
	 */
	void set_target(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the ID of the event a given timer starts/ends.
	 * \param Entity system which contains the timer.
	 * \param ID of the timer.
	 */
	tdt::uint get_target(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the type of a given timer.
	 * \param Entity system which contains the timer.
	 * \param ID of the timer.
	 * \param The new type.
	 */
	void set_type(EntitySystem&, tdt::uint, TIME_EVENT);

	/**
	 * \brief Returns the type of a given timer.
	 * \param Entity system which contains the timer.
	 * \param ID of the timer.
	 */
	TIME_EVENT get_type(EntitySystem&, tdt::uint);
}