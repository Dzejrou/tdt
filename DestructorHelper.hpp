#pragma once

#include <string>
#include "Components.hpp"
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the destructor component.
 */
namespace DestructorHelper
{
	/**
	 * Brief: Sets the name of the table that contains the "dtor" function
	 *        which get's called when a given entity is destroyed.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: The new blueprint table's name.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * Brief: Returns the name of the table that contains the "dtor" function
	 *        which get's called when a given entity is destroyed.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * Brief: Destroys a given entity and if possible calls it's destructor.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: If true, the destructor won't be called.
	 * Param: ID of the killer (if any).
	 */
	void destroy(EntitySystem&, tdt::uint, bool = false, tdt::uint = Component::NO_ENTITY);
}