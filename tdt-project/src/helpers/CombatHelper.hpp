#pragma once

#include <tuple>
#include <Typedefs.hpp>
#include <Enums.hpp>
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the combat component.
 */
namespace CombatHelper
{
	/**
	 * \brief Changes the target of a given entity's attack.
	 * \param EntitySystem containing the entity and it's target.
	 * \param ID of the entity.
	 * \param ID of the target.
	 */
	void set_target(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the target of a given entity's attack.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_target(EntitySystem&, tdt::uint);

	/**
	 * \brief Changes the attack range of a given entity.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 * \param The new attack range.
	 */
	void set_range(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the attack range of a given entity.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_range(EntitySystem&, tdt::uint);

	/**
	 * \brief Changes the damage range (min damage, max damage) that a given
	 *        entity can deal when attacking.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 * \param Minimal damage value.
	 * \param Maximal damage value.
	 */
	void set_dmg_range(EntitySystem&, tdt::uint, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the damage range (in the form of a 2-member tuple) of
	 *        a given entity.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 */
	std::tuple<tdt::uint, tdt::uint> get_dmg_range(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns a pseudo random damage value between given two numbers,
	 *        used to calculate the damage of each individual attack.
	 * \param Minimal damage value.
	 * \param Maximal damage value.
	 */
	tdt::uint get_dmg(tdt::uint, tdt::uint);

	/**
	 * \brief Changes the cooldown (minimal time between attacks) of a given entity.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 * \param The new cooldown value.
	 */
	void set_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the cooldown (minimal time between attacks) of a given entity.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_cooldown(EntitySystem&, tdt::uint);

	/**
	 * \brief Changes the attack type of a given entity.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 * \param The new attack type.
	 */
	void set_atk_type(EntitySystem&, tdt::uint, ATTACK_TYPE);

	/**
	 * \brief Returns the attack type of a given entity.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 */
	ATTACK_TYPE get_atk_type(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns true if a given entity is in attack range from
	 *        another entity.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity checking range.
	 * \param ID of the second entity.
	 */
	bool in_range(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the projectile table used when a given entity shoots.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 * \param Name of the projectile table.
	 */
	void set_projectile_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the projectile table used when a given entity shoots.
	 * \param EntitySystem containing the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_projectile_blueprint(EntitySystem&, tdt::uint);
}