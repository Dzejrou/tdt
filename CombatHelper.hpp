#pragma once

#include <Ogre.h>
#include <tuple>
#include <random>
#include <numeric>
#include <cstdlib>
#include "Enums.hpp"
class EntitySystem;

namespace CombatHelper
{
	/**
	 * Brief: Changes the target of a given entity's attack.
	 * Param: EntitySystem containing the entity and it's target.
	 * Param: ID of the entity.
	 * Param: ID of the target.
	 */
	void set_target(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the target of a given entity's attack.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get_target(EntitySystem&, std::size_t);

	/**
	 * Brief: Changes the attack range of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: The new attack range.
	 */
	void set_range(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the attack range of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_range(EntitySystem&, std::size_t);

	/**
	 * Brief: Changes the damage range (min damage, max damage) that a given
	 *        entity can deal when attacking.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: Minimal damage value.
	 * Param: Maximal damage value.
	 */
	void set_dmg_range(EntitySystem&, std::size_t, std::size_t, std::size_t);

	/**
	 * Brief: Returns the damage range (in the form of a 2-member tuple) of
	 *        a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	std::tuple<std::size_t, std::size_t> get_dmg_range(EntitySystem&, std::size_t);

	/**
	 * Brief: Returns a pseudo random damage value between given two numbers,
	 *        used to calculate the damage of each individual attack.
	 * Param: Minimal damage value.
	 * Param: Maximal damage value.
	 */
	std::size_t get_dmg(std::size_t, std::size_t);

	/**
	 * Brief: Changes the cooldown (minimal time between attacks) of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: The new cooldown value.
	 */
	void set_cooldown(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the cooldown (minimal time between attacks) of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_cooldown(EntitySystem&, std::size_t);

	/**
	 * Brief: Changes the attack type of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: The new attack type.
	 */
	void set_atk_type(EntitySystem&, std::size_t, ATTACK_TYPE);

	/**
	 * Brief: Returns the attack type of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	ATTACK_TYPE get_atk_type(EntitySystem&, std::size_t);
}