#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the health component.
 */
namespace HealthHelper
{
	/**
	 * \brief Sets the health of a given entity without any regard to it's maximal health.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param The new health value.
	 */
	void set_health(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the current health amount of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	tdt::uint get_health(EntitySystem&, tdt::uint);

	/**
	 * \brief Increases the current health amount of an entity by a given amount
	 *        up to the maximum value stored in it's HealthComponent.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param Amount of health to be added.
	 * Node: To increase health along with the maximum value, see HealthSystem::buff.
	 */
	void add_health(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Subtracts a given amount from the current health of an entity, taking
	 *        it's defense into account by default.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param Amount of health to be subtracted.
	 * \param Optional boolean indicator, if true, the entity's defense will be ignored,
	 *        otherwise it will be subtracted from the given amount.
	 */
	void sub_health(EntitySystem&, tdt::uint, tdt::uint, bool = false);

	/**
	 * \brief Sets the current health amount of an entity to it's maximum value.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	void heal(EntitySystem&, tdt::uint);

	/**
	 * \brief Increases the current and maximum health amount of an entity by a given value.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param Amount of health to be added.
	 */
	void buff(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Reduces the current and maximum health amount of an entity by a given value.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param Amount of health to be subtracted.
	 */
	void debuff(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the regeneration value of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param The new regen value.
	 */
	void set_regen(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the regeneration value of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID o fthe entity.
	 */
	tdt::uint get_regen(EntitySystem&, tdt::uint);

	/**
	 * \brief Allows to set the health status of an entity without adding/subing health.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param True for "alive" and false for "dead".
	 */
	void set_alive(EntitySystem&, tdt::uint, bool);

	/**
	 * \brief Returns true if a given entity is alive, false otherwise.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	bool is_alive(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the amount of defense a given entity has to a given
	 *        (absolute) amount.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param The new defense value.
	 */
	void set_defense(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the defense of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	tdt::uint get_defense(EntitySystem&, tdt::uint);

	/**
	 * \brief Increases the defense of an entity by a given amount.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param Amount of defense to be added.
	 */
	void add_defense(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Reduces the defense of an entity by a given amount.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param Amounf of defense to be removed.
	 */
	void sub_defense(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief A cheat that sets the health, maximum health and defense to their
	 *        highest possible values.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	void ubercharge(EntitySystem&, tdt::uint);
}