#pragma once

#include <string>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace that contains functions that help with the management
 * of the spell component.
 */
namespace SpellHelper
{
	/**
	 * \brief Sets the blueprint table of the spell a given entity can
	 *        cast.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new spell blueprint.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the blueprint table of the spell a given entity can
	 *        cast.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the time period between casts of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new cooldown value.
	 */
	void set_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the time period between casts of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_cooldown(EntitySystem&, tdt::uint);

	/**
	 * \brief Advances the timer before the next spell can be cast
	 *        by a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param Time to advance by.
	 */
	void advance_curr_time(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Sets the timer before the next spell can be cast
	 *        by a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new timer value (cooldown - timer == time remaining).
	 */
	void set_curr_time(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the cooldown timer value of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_curr_time(EntitySystem&, tdt::uint);

	/**
	 * \brief Makes a given entity to cast it's spell (if possible).
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \note Ignores cooldown.
	 */
	void cast(EntitySystem&, tdt::uint);
}