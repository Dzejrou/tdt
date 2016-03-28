#pragma once

#include <string>
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the notification component.
 */
namespace NotificationHelper
{
	/**
	 * Brief: Sets the cooldown between notifications a given entity
	 *        can send to the game's log.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new cooldown.
	 */
	void set_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the cooldown between notifications a given entity
	 *        can send to the game's log.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_cooldown(EntitySystem&, tdt::uint);

	/**
	 * Brief: Resets the cooldown between notifications a given entity
	 *        can send to the game's log. (That means that the entity
	 *        can notify immediately.)
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	void reset(EntitySystem&, tdt::uint);

	/**
	 * Param: Sends a notification to the game's log while respecting
	 *        the notification cooldown of the entity that sends the
	 *        notification. (And sets the cooldown if needed.)
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	bool notify(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * Brief: Returns the time since the last notification a given entity
	 *        has sent to the game's log.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_curr_time(EntitySystem&, tdt::uint);

	/**
	 * Brief: Advances the time since the last notification a given entity
	 *        has sent to the game's log.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: Time amount to advance by.
	 */
	void advance_curr_time(EntitySystem&, tdt::uint, tdt::real);
}