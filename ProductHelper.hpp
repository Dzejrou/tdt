#pragma once

#include <cstdlib>
class EntitySystem;

namespace ProductHelper
{
	/**
	 * Brief: Set's the producer of a given entity (the building that
	 *        spawned it).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: ID of the producer.
	 */
	void set_producer(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the producer of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	std::size_t get_producer(EntitySystem&, std::size_t);
}