#pragma once

#include <string>
#include "Typedefs.hpp"
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
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * Brief: Returns the name of the blueprint table that handles the construction
	 *        of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * Brief: Calls the blueprint table that handles the construction
	 *        of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	void call(EntitySystem&, tdt::uint);
}