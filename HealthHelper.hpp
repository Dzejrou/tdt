#pragma once

#include "Components.hpp"
#include "EntitySystem.hpp"

namespace HealthHelper
{
	/**
	 * Brief: Sets the health of a given entity without any regard to it's maximal health.
	 * Param: ID of the entity.
	 * Param: The new health value.
	 */
	void set_health(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the current health amount of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	std::size_t get_health(EntitySystem&, std::size_t);

	/**
	 * Brief: Increases the current health amount of an entity by a given amount
	 *        up to the maximum value stored in it's HealthComponent.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amount of health to be added.
	 * Node: To increase health along with the maximum value, see HealthSystem::buff.
	 */
	void add_health(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Subtracts a given amount from the current health of an entity, taking
	 *        it's defense into account by default.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amount of health to be subtracted.
	 * Param: Optional boolean indicator, if true, the entity's defense will be ignored,
	 *        otherwise it will be subtracted from the given amount.
	 */
	void sub_health(EntitySystem&, std::size_t, std::size_t, bool = false);

	/**
	 * Brief: Sets the current health amount of an entity to it's maximum value.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	void heal(EntitySystem&, std::size_t);

	/**
	 * Brief: Increases the current and maximum health amount of an entity by a given value.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amount of health to be added.
	 */
	void buff(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Reduces the current and maximum health amount of an entity by a given value.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amount of health to be subtracted.
	 */
	void debuff(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Sets the regeneration value of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: The new regen value.
	 */
	void set_regen(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the regeneration value of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID o fthe entity.
	 */
	std::size_t get_regen(EntitySystem&, std::size_t);

	/**
	 * Brief: Allows to set the health status of an entity without adding/subing health.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: True for "alive" and false for "dead".
	 */
	void set_alive(EntitySystem&, std::size_t, bool);

	/**
	 * Brief: Returns true if a given entity is alive, false otherwise.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	bool is_alive(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the amount of defense a given entity has to a given
	 *        (absolute) amount.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: The new defense value.
	 */
	void set_defense(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the defense of a given entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	std::size_t get_defense(EntitySystem&, std::size_t);

	/**
	 * Brief: Increases the defense of an entity by a given amount.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amount of defense to be added.
	 */
	void add_defense(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Reduces the defense of an entity by a given amount.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Amounf of defense to be removed.
	 */
	void sub_defense(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: A cheat that sets the health, maximum health and defense to their
	 *        highest possible values.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	void ubercharge(EntitySystem&, std::size_t);
}