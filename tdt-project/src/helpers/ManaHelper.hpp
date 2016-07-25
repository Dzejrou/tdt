#pragma once

#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace that contains functions that help with the management
 * of the mana component.
 */
namespace ManaHelper
{
	/**
	 * \brief Adds a given amount of mana to a given entity's
	 *        current mana pool.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param Amount of mana to add.
	 */
	void add_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Removes a given amount of mana from a given entity's
	 *        current mana pool.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param Amount of mana to subtract.
	 */
	bool sub_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the amount of mana a given entity has to a given
	 *        amount.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new amount of mana.
	 */
	void set_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the amount of mana a given entity has.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_mana(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the max amount of mana a given entity can have.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new mana limit.
	 */
	void set_max_mana(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the max amount of mana a given entity can have.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_max_mana(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the mana regeneration value of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new mana regeneration value.
	 */
	void set_regen(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the mana regeneration value of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_regen(EntitySystem&, tdt::uint);

}