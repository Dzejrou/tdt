#pragma once

#include <string>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the on hit component.
 */
namespace OnHitHelper
{
	/**
	 * \brief Sets the blueprint table handling incoming hits of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new blueprint name.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the name of the on hit blueprint of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * \brief Calls the on hit handler of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param ID of the hitter. (Source of the attack.)
	 */
	void call(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the cooldown between on hit blueprint calls of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 * \param The new cooldown.
	 */
	void set_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the cooldown between on hit blueprint calls of a given entity.
	 * \param EntitySystem that contains the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_cooldown(EntitySystem&, tdt::uint);
}