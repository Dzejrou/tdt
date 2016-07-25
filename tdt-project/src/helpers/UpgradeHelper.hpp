#pragma once

#include <string>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the upgrade component.
 */
namespace UpgradeHelper
{
	/**
	 * \brief Sets the blueprint table that handles the upgrading of
	 *        a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new blueprint name.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the blueprint table that handles the upgrading of
	 *        a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the amount of experience a given entity has. Won't allow
	 *        more experience than is needed for the next level and returns the
	 *        remaining experience not added.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new experience amount.
	 */
	tdt::uint set_experience(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the amount of experience a given entity has.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_experience(EntitySystem&, tdt::uint);

	/**
	 * \brief Adds a given amount of experience to a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The amount of experience to be added.
	 */
	tdt::uint add_experience(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the amount of experience needed for next level of a
	 *        given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new experience amount needed.
	 */
	void set_exp_needed(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the amount of experience needed for next level of a
	 *        given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_exp_needed(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the level of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new level.
	 * \note Does not change the attributes of the entity!
	 */
	void set_level(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the level of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_level(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the maximum level a given entity can reach.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new max level.
	 */
	void set_level_cap(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the maximum level a given entity can reach.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::uint get_level_cap(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns true if a given entity can level up.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	bool can_level_up(EntitySystem&, tdt::uint);

	/**
	 * \brief Upgrades a given entity that can level up.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	void upgrade(EntitySystem&, tdt::uint);
}