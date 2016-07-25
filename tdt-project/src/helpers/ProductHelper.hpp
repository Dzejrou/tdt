#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of the
 * product component.
 */
namespace ProductHelper
{
	/**
	 * \brief Set's the producer of a given entity (the building that
	 *        spawned it).
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param ID of the producer.
	 */
	void set_producer(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the producer of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	tdt::uint get_producer(EntitySystem&, tdt::uint);
}