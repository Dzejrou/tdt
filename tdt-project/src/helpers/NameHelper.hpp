#pragma once

#include <string>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the name component.
 */
namespace NameHelper
{
	/**
	 * \brief Sets the name of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 * \param The new name.
	 */
	void set_name(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the name of a given entity.
	 * \param Entity system containing the entity.
	 * \param ID of the entity.
	 */
	const std::string& get_name(EntitySystem&, tdt::uint);
}