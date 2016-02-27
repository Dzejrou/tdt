#pragma once

#include <Ogre.h>
#include <cstdlib>
#include <string>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the
 * management of the trigger component.
 */
namespace TriggerHelper
{
	/**
	 * Brief: Sets the blueprint table used used to handle triggering
	 *        of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new blueprint name.
	 */
	void set_blueprint(EntitySystem&, std::size_t, const std::string&);

	/**
	 * Brief: Returns the blueprint table used used to handle triggering
	 *        of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, std::size_t);

	/**
	 * Param: Sets the linked entity a given trigger entity is linked to.
	 * Param: Entity system containing the entity.
	 * Param: ID of the trigger entity.
	 * Param: ID of the linked entity.
	 */
	void set_linked_entity(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Param: Returns the ID of the entity a given trigger entity is
	 *        linked to.
	 * Param: Entity system containing the entity.
	 * Param: ID of the trigger entity.
	 */
	std::size_t get_linked_entity(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the cooldown before an entity can be triggered
	 *        again.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	void set_cooldown(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the cooldown before an entity can be triggered
	 *        again.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_cooldown(EntitySystem&, std::size_t);

	/**
	 * Param: Triggers an entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the triggered entity.
	 * Param: ID of the entity that triggered the triggered entity.
	 */
	void trigger(EntitySystem&, std::size_t, std::size_t);
}