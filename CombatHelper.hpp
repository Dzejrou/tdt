#pragma once

#include <tuple>
#include "Enums.hpp"
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the combat component.
 */
namespace CombatHelper
{
	/**
	 * Brief: Changes the target of a given entity's attack.
	 * Param: EntitySystem containing the entity and it's target.
	 * Param: ID of the entity.
	 * Param: ID of the target.
	 */
	void set_target(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the target of a given entity's attack.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::uint get_target(EntitySystem&, tdt::uint);

	/**
	 * Brief: Changes the attack range of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: The new attack range.
	 */
	void set_range(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the attack range of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_range(EntitySystem&, tdt::uint);

	/**
	 * Brief: Changes the damage range (min damage, max damage) that a given
	 *        entity can deal when attacking.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: Minimal damage value.
	 * Param: Maximal damage value.
	 */
	void set_dmg_range(EntitySystem&, tdt::uint, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the damage range (in the form of a 2-member tuple) of
	 *        a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	std::tuple<tdt::uint, tdt::uint> get_dmg_range(EntitySystem&, tdt::uint);

	/**
	 * Brief: Returns a pseudo random damage value between given two numbers,
	 *        used to calculate the damage of each individual attack.
	 * Param: Minimal damage value.
	 * Param: Maximal damage value.
	 */
	tdt::uint get_dmg(tdt::uint, tdt::uint);

	/**
	 * Brief: Changes the cooldown (minimal time between attacks) of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: The new cooldown value.
	 */
	void set_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the cooldown (minimal time between attacks) of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_cooldown(EntitySystem&, tdt::uint);

	/**
	 * Brief: Changes the attack type of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: The new attack type.
	 */
	void set_atk_type(EntitySystem&, tdt::uint, ATTACK_TYPE);

	/**
	 * Brief: Returns the attack type of a given entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	ATTACK_TYPE get_atk_type(EntitySystem&, tdt::uint);

	/**
	 * Brief: Returns true if a given entity is in attack range from
	 *        another entity.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity checking range.
	 * Param: ID of the second entity.
	 */
	bool in_range(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Sets the projectile table used when a given entity shoots.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 * Param: Name of the projectile table.
	 */
	void set_projectile_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * Brief: Returns the projectile table used when a given entity shoots.
	 * Param: EntitySystem containing the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_projectile_blueprint(EntitySystem&, tdt::uint);
}