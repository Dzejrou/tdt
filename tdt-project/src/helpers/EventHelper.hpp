#pragma once

#include <Enums.hpp>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the event component.
 */
namespace EventHelper
{
	/**
	 * \brief Sets the type of a given event.
	 * \param Entity system that contains the entity.
	 * \param ID of the event.
	 * \param The new type.
	 */
	void set_event_type(EntitySystem&, tdt::uint, EVENT_TYPE);

	/**
	 * \brief Returns the type of a given event.
	 * \param Entity system that contains the entity.
	 * \param ID of the event.
	 */
	EVENT_TYPE get_event_type(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the target entity (the subject of the event) of
	 *        a given event.
	 * \param Entity system that contains the entity.
	 * \param ID of the event.
	 * \param ID of the target.
	 */
	void set_target(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the target entity (the subject of the event) of
	 *        a given event.
	 * \param Entity system that contains the entity.
	 * \param ID of the event.
	 */
	tdt::uint get_target(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the radius handlers have to be in in order to be
	 *        able to handle a given event.
	 * \param Entity system that contains the entity.
	 * \param ID of the event.
	 * \param The new radius.
	 */
	void set_radius(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the radius handlers have to be in in order to be
	 *        able to handle a given event.
	 * \param Entity system that contains the entity.
	 * \param ID of the event.
	 */
	tdt::real get_radius(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the activity state of a given event.
	 * \param Entity system that contains the entity.
	 * \param ID of the event.
	 * \param ID for active, false for inactive.
	 */
	void set_active(EntitySystem&, tdt::uint, bool = true);

	/**
	 * \brief Returns true if a given event is active,
	 *        false otherwise.
	 * \param Entity system that contains the entity.
	 * \param ID of the event.
	 */
	bool is_active(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the entity that handles a given event.
	 * \param Entity system containing both the entity and the event.
	 * \param ID of the event.
	 * \param ID of the handling entity.
	 */
	void set_event_handler(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the entity that handles a given event.
	 * \param Entity system containing both the entity and the event.
	 * \param ID of the event.
	 */
	tdt::uint get_event_handler(EntitySystem&, tdt::uint);
}