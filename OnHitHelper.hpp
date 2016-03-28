#pragma once

#include <string>
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the on hit component.
 */
namespace OnHitHelper
{
	/**
	 * Brief: Sets the blueprint table handling incoming hits of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new blueprint name.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * Brief: Returns the name of the on hit blueprint of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * Brief: Calls the on hit handler of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: ID of the hitter. (Source of the attack.)
	 */
	void call(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Sets the cooldown between on hit blueprint calls of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new cooldown.
	 */
	void set_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the cooldown between on hit blueprint calls of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_cooldown(EntitySystem&, tdt::uint);
}