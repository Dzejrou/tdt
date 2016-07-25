#pragma once

#include <string>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the
 * management of the trigger component.
 */
namespace TriggerHelper
{
	/**
	 * \brief Sets the blueprint table used used to handle triggering
	 *        of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new blueprint name.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the blueprint table used used to handle triggering
	 *        of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * \param Sets the linked entity a given trigger entity is linked to.
	 * \param Entity system containing the entity.
	 * \param ID of the trigger entity.
	 * \param ID of the linked entity.
	 */
	void set_linked_entity(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \param Returns the ID of the entity a given trigger entity is
	 *        linked to.
	 * \param Entity system containing the entity.
	 * \param ID of the trigger entity.
	 */
	tdt::uint get_linked_entity(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the cooldown before an entity can be triggered
	 *        again.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	void set_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the cooldown before an entity can be triggered
	 *        again.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_cooldown(EntitySystem&, tdt::uint);

	/**
	 * \brief Triggers an entity.
	 * \param Entity system containing the entity.
	 * \param ID of the triggered entity.
	 * \param ID of the entity that triggered the triggered entity.
	 */
	void trigger(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns true if a given entity can be triggered by another
	 *        given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity that is supposed to get triggered.
	 * \param ID of the triggering entity.
	 */
	bool can_be_triggered_by(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the trigger cooldown timer of a given entity to zero. 
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	void reset_timer(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the trigger radius of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	void set_radius(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the trigger radius of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	tdt::real get_radius(EntitySystem&, tdt::uint);
}