#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of the
 * product component.
 */
namespace ProductHelper
{
	/**
	 * Brief: Set's the producer of a given entity (the building that
	 *        spawned it).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: ID of the producer.
	 */
	void set_producer(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the producer of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	tdt::uint get_producer(EntitySystem&, tdt::uint);
}