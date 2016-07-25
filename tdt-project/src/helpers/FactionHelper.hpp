#pragma once

#include <string>
#include <Enums.hpp>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management
 * of the faction component.
 */
namespace FactionHelper
{
	/**
	 * \brief Changes the FACTION of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param The new faction.
	 */
	void set_faction(EntitySystem&, tdt::uint, FACTION);

	/**
	 * \brief Returns the FACTION of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	FACTION get_faction(EntitySystem&, tdt::uint);

	/**
	 * \brief Returns the FACTION name (a string) of a given entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	const std::string& get_faction_name(EntitySystem&, tdt::uint);
}