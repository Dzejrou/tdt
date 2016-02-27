#pragma once

#include <Ogre.h>
#include <cstdlib>
#include <string>
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
	void set_blueprint(EntitySystem&, std::size_t, const std::string&);

	/**
	 * Brief: Returns the name of the on hit blueprint of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, std::size_t);

	/**
	 * Brief: Calls the on hit handler of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: ID of the hitter. (Source of the attack.)
	 */
	void call(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Sets the cooldown between on hit blueprint calls of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new cooldown.
	 */
	void set_cooldown(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the cooldown between on hit blueprint calls of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_cooldown(EntitySystem&, std::size_t);
}