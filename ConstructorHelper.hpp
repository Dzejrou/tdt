#pragma once

#include <cstdlib>
#include <string>
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with constructor component
 * management.
 */
namespace ConstructorHelper
{
	/**
	 * Brief: Sets the name of the blueprint table that handles the construction
	 *        of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new blueprint name.
	 */
	void set_blueprint(EntitySystem&, std::size_t, const std::string&);

	/**
	 * Brief: Returns the name of the blueprint table that handles the construction
	 *        of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, std::size_t);

	/**
	 * Brief: Calls the blueprint table that handles the construction
	 *        of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	void call(EntitySystem&, std::size_t);
}