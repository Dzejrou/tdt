#pragma once

#include <string>
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace that contains functions that help with the management
 * of the spell component.
 */
namespace SpellHelper
{
	/**
	 * Brief: Sets the blueprint table of the spell a given entity can
	 *        cast.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new spell blueprint.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * Brief: Returns the blueprint table of the spell a given entity can
	 *        cast.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the time period between casts of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new cooldown value.
	 */
	void set_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the time period between casts of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_cooldown(EntitySystem&, tdt::uint);

	/**
	 * Brief: Advances the timer before the next spell can be cast
	 *        by a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: Time to advance by.
	 */
	void advance_curr_time(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Sets the timer before the next spell can be cast
	 *        by a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Param: The new timer value (cooldown - timer == time remaining).
	 */
	void set_curr_time(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * Brief: Returns the cooldown timer value of a given entity.
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 */
	tdt::real get_curr_time(EntitySystem&, tdt::uint);

	/**
	 * Brief: Makes a given entity to cast it's spell (if possible).
	 * Param: EntitySystem that contains the entity.
	 * Param: ID of the entity.
	 * Note: Ignores cooldown.
	 */
	void cast(EntitySystem&, tdt::uint);
}