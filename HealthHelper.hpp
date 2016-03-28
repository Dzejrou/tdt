#pragma once

#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the health component.
 */
namespace HealthHelper
{
	/**
	 * Brief: Sets the health of a given entity without any regard to it's maximal health.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: The new health value.
	 */
	void set_health(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the current health amount of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	tdt::uint get_health(EntitySystem&, tdt::uint);

	/**
	 * Brief: Increases the current health amount of an entity by a given amount
	 *        up to the maximum value stored in it's HealthComponent.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amount of health to be added.
	 * Node: To increase health along with the maximum value, see HealthSystem::buff.
	 */
	void add_health(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Subtracts a given amount from the current health of an entity, taking
	 *        it's defense into account by default.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amount of health to be subtracted.
	 * Param: Optional boolean indicator, if true, the entity's defense will be ignored,
	 *        otherwise it will be subtracted from the given amount.
	 */
	void sub_health(EntitySystem&, tdt::uint, tdt::uint, bool = false);

	/**
	 * Brief: Sets the current health amount of an entity to it's maximum value.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	void heal(EntitySystem&, tdt::uint);

	/**
	 * Brief: Increases the current and maximum health amount of an entity by a given value.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amount of health to be added.
	 */
	void buff(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Reduces the current and maximum health amount of an entity by a given value.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amount of health to be subtracted.
	 */
	void debuff(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Sets the regeneration value of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: The new regen value.
	 */
	void set_regen(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the regeneration value of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID o fthe entity.
	 */
	tdt::uint get_regen(EntitySystem&, tdt::uint);

	/**
	 * Brief: Allows to set the health status of an entity without adding/subing health.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: True for "alive" and false for "dead".
	 */
	void set_alive(EntitySystem&, tdt::uint, bool);

	/**
	 * Brief: Returns true if a given entity is alive, false otherwise.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	bool is_alive(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the amount of defense a given entity has to a given
	 *        (absolute) amount.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: The new defense value.
	 */
	void set_defense(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the defense of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	tdt::uint get_defense(EntitySystem&, tdt::uint);

	/**
	 * Brief: Increases the defense of an entity by a given amount.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amount of defense to be added.
	 */
	void add_defense(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Reduces the defense of an entity by a given amount.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amounf of defense to be removed.
	 */
	void sub_defense(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: A cheat that sets the health, maximum health and defense to their
	 *        highest possible values.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	void ubercharge(EntitySystem&, tdt::uint);
}