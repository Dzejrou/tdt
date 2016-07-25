#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace that contains functions that help with the management
 * of the mana crystal component.
 */
namespace ManaCrystalHelper
{
	/**
	 * \brief Sets the amount of max mana this entity adds
	 *        to the player's mana capacity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new capacity value.
	 */
	void set_capacity(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the amount of max mana this entity adds
	 *        to the player's mana capacity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_capacity(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the amount of mana regen this entity adds
	 *        to the player's total mana regen.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new capacity value.
	 */
	void set_regen(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the amount of mana regen this entity adds
	 *        to the player's total mana regen.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_regen(EntitySystem&, tdt::uint);
}