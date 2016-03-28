#pragma once

#include <vector>
#include "Typedefs.hpp"
class EntitySystem;

/**
 * Auxiliary namespace containing the functions that help with the management
 * of the structure component.
 */
namespace StructureHelper
{
	/**
	 * Brief: Adds the members of a given vector (containing node IDs) as residences
	 *        of a given entity (that has a structure component).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Vector containing the IDs of the new residences (nodes the entity is on).
	 */
	void add_residences(EntitySystem&, tdt::uint, const std::vector<tdt::uint>&);

	/**
	 * Brief: Adds a single node as a residence to the residence list of a given
	 *        entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the structure.
	 * Param: ID of the residence.
	 */
	void add_residence(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Sets the radius of the area a given structure occupies.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity (which has a structure component).
	 * Param: The new radius.
	 */
	void set_radius(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * Brief: Returns the radius of a structure (amount of grid nodes from the
	 *        centre of the structure to one of the sides - not including the centre).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	tdt::uint get_radius(EntitySystem&, tdt::uint);

	/**
	 * Brief: Sets the walk through field of a structure, causing it
	 *        to either block or allow pathfinding.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the structure.
	 * Param: True for walkable, false for not walkable.
	 */
	void set_walk_through(EntitySystem&, tdt::uint, bool);

	/**
	 * Brief: Returns true if pathfinding is possible through the structure,
	 *        false otherwise.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the structure.
	 */
	bool is_walk_through(EntitySystem&, tdt::uint);
}