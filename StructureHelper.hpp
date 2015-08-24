#pragma once

class EntitySystem;

namespace StructureHelper
{
	/**
	 * Brief: Adds the members of a given vector (containing node IDs) as residences
	 *        of a given entity (that has a structure component).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 * Param: Vector containing the IDs of the new residences (nodes the entity is on).
	 */
	void add_residences(EntitySystem&, std::size_t, const std::vector<std::size_t>&);

	/**
	 * Brief: Adds a single node as a residence to the residence list of a given
	 *        entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the structure.
	 * Param: ID of the residence.
	 */
	void add_residence(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Sets the radius of the area a given structure occupies.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity (which has a structure component).
	 * Param: The new radius.
	 */
	void set_radius(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the radius of a structure (amount of grid nodes from the
	 *        centre of the structure to one of the sides - not including the centre).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	std::size_t get_radius(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the walk through field of a structure, causing it
	 *        to either block or allow pathfinding.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the structure.
	 * Param: True for walkable, false for not walkable.
	 */
	void set_walk_through(EntitySystem&, std::size_t, bool);

	/**
	 * Brief: Returns true if pathfinding is possible through the structure,
	 *        false otherwise.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the structure.
	 */
	bool is_walk_through(EntitySystem&, std::size_t);
}