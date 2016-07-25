#pragma once

#include <string>
#include <Enums.hpp>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Namespace containing auxiliary functions that help with the management of
 * the ai component.
 */
namespace AIHelper
{
	/**
	 * \brief Changes the blueprint table name of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param Name of the new blueprint table.
	 */
	void set_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns name of the blueprint table of a given entity (i.e. the table containing
	 *        it's init, update and finnish methods).
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, tdt::uint);

	/**
	 * \brief Changes the state of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param New state.
	 */
	void set_state(EntitySystem&, tdt::uint, ENTITY_STATE::VAL);

	/**
	 * \brief Returns the state a given entity is in.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	ENTITY_STATE::VAL get_state(EntitySystem&, tdt::uint);
}