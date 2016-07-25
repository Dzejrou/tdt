#pragma once

#include <vector>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing the functions that help with the management
 * of the structure component.
 */
namespace StructureHelper
{
	/**
	 * \brief Adds the members of a given vector (containing node IDs) as residences
	 *        of a given entity (that has a structure component).
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 * \param Vector containing the IDs of the new residences (nodes the entity is on).
	 */
	void add_residences(EntitySystem&, tdt::uint, const std::vector<tdt::uint>&);

	/**
	 * \brief Adds a single node as a residence to the residence list of a given
	 *        entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the structure.
	 * \param ID of the residence.
	 */
	void add_residence(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Sets the radius of the area a given structure occupies.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity (which has a structure component).
	 * \param The new radius.
	 */
	void set_radius(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the radius of a structure (amount of grid nodes from the
	 *        centre of the structure to one of the sides - not including the centre).
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	tdt::uint get_radius(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the walk through field of a structure, causing it
	 *        to either block or allow pathfinding.
	 * \param Reference to the entity system containing components.
	 * \param ID of the structure.
	 * \param True for walkable, false for not walkable.
	 */
	void set_walk_through(EntitySystem&, tdt::uint, bool);

	/**
	 * \brief Returns true if pathfinding is possible through the structure,
	 *        false otherwise.
	 * \param Reference to the entity system containing components.
	 * \param ID of the structure.
	 */
	bool is_walk_through(EntitySystem&, tdt::uint);
}