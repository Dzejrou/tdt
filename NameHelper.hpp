#pragma once

#include <cstdlib>
#include <string>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the name component.
 */
namespace NameHelper
{
	/**
	 * Brief: Sets the name of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new name.
	 */
	void set_name(EntitySystem&, std::size_t, const std::string&);

	/**
	 * Brief: Returns the name of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_name(EntitySystem&, std::size_t);
}