#pragma once

#include "Enums.hpp"
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of the
 * time component.
 */
namespace TimeHelper
{
	/**
	 * Brief: Returns the time that has passed since the timer started.
	 * Param: Entity system which contains the timer.
	 * Param: ID of th entity.
	 */
	tdt::real get_curr_time(EntitySystem&, tdt::uint);

	/**
	 * Brief: Adds a given time value to a given timer.
	 * Param: Entity system which contains the timer.
	 * Param: ID of the timer.
	 * Param: Time to add.
	 */
	void advance_curr_time(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Completes a given timer (by maxing it's current time).
	 * Param: Entity system which contains the timer.
	 * Param: ID of the timer.
	 */
	void max_curr_time(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the time a given timer requires for completion.
	 * Param: Entity system which contains the timer.
	 * Param: ID of the timer.
	 * Param: The new time limit.
	 */
	void set_time_limit(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the time a given timer requires for completion.
	 * Param: Entity system which contains the timer.
	 * Param: ID of the timer.
	 */
	tdt::real get_time_limit(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the ID of the event a given timer starts/ends.
	 * Param: Entity system which contains the timer.
	 * Param: ID of the timer.
	 * Param: ID of the event.
	 */
	void set_target(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the ID of the event a given timer starts/ends.
	 * Param: Entity system which contains the timer.
	 * Param: ID of the timer.
	 */
	tdt::uint get_target(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the type of a given timer.
	 * Param: Entity system which contains the timer.
	 * Param: ID of the timer.
	 * Param: The new type.
	 */
	void set_type(EntitySystem&, tdt::uint, TIME_EVENT);

	/**
	 * Brief: Returns the type of a given timer.
	 * Param: Entity system which contains the timer.
	 * Param: ID of the timer.
	 */
	TIME_EVENT get_type(EntitySystem&, tdt::uint);
}