#pragma once

#include <string>
#include <Enums.hpp>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the event handler component.
 */
namespace EventHandlerHelper
{
	/**
	 * \brief Sets the name of the table that contains event the handler function
	 *        of a given entity.
	 * \param Entity system that contains the entity.
	 * \param ID of the entity.
	 * \param The new handler table name.
	 */
	void set_handler(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the name of the table that contains event the handler function
	 *        of a given entity.
	 * \param Entity system that contains the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_handler(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns true if a given entity can handle a given event.
	 * \param Entity system that contains the entity.
	 * \param ID of the entity.
	 * \param The type of the event.
	 */
	bool can_handle(EntitySystem&, tdt::uint, EVENT_TYPE);

	/**
	 * \brief Adds a given event into the list of possible events of a
	 *        given entity.
	 * \param Entity system that contains the entity.
	 * \param ID of the entity.
	 * \param The type of the event.
	 */
	void add_possible_event(EntitySystem&, tdt::uint, EVENT_TYPE);

	/**
	 * \brief Removes a given event from the list of possible events of a
	 *        given entity.
	 * \param Entity system that contains the entity.
	 * \param ID of the entity.
	 * \param The type of the event.
	 */
	void delete_possible_event(EntitySystem&, tdt::uint, EVENT_TYPE);
}