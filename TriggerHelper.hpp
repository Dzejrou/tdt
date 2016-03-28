#pragma once

#include <string>
#include "Typedefs.hpp"
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
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * Brief: Returns the blueprint table used used to handle triggering
	 *        of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * Param: Sets the linked entity a given trigger entity is linked to.
	 * Param: Entity system containing the entity.
	 * Param: ID of the trigger entity.
	 * Param: ID of the linked entity.
	 */
	void set_linked_entity(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Param: Returns the ID of the entity a given trigger entity is
	 *        linked to.
	 * Param: Entity system containing the entity.
	 * Param: ID of the trigger entity.
	 */
	tdt::uint get_linked_entity(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the cooldown before an entity can be triggered
	 *        again.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	void set_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the cooldown before an entity can be triggered
	 *        again.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_cooldown(EntitySystem&, tdt::uint);

	/**
	 * Brief: Triggers an entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the triggered entity.
	 * Param: ID of the entity that triggered the triggered entity.
	 */
	void trigger(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns true if a given entity can be triggered by another
	 *        given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity that is supposed to get triggered.
	 * Param: ID of the triggering entity.
	 */
	bool can_be_triggered_by(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Sets the trigger cooldown timer of a given entity to zero. 
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	void reset_timer(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the trigger radius of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	void set_radius(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the trigger radius of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_radius(EntitySystem&, tdt::uint);
}