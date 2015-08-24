#pragma once

#include <string>
#include <cstdlib>
class EntitySystem;

namespace ProductionHelper
{
	/**
	 * Brief: Changes the name of the blueprint table used to
	 *        spawn new entities.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the building.
	 * Param: Name of the new building table.
	 */
	void set_production_blueprint(EntitySystem&, std::size_t, const std::string&);

	/**
	 * Brief: Returns the name of the blueprint table used to
	 *        spawn new entities.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the building.
	 */
	const std::string& get_production_blueprint(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the maximal number of entities a given building
	 *        can spawn.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the building.
	 * Param: The new entity limit.
	 */
	void set_production_limit(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the maximal number of entities a given building
	 *        can spawn.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the building.
	 */
	std::size_t get_production_limit(EntitySystem&, std::size_t);
	
	/**
	 * Brief: Sets the time it takes for a given building to spawn
	 *        a single entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the building.
	 * Param: The new entity spawning time.
	 */
	void set_production_cooldown(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the time it takes for a given building to spawn
	 *        a single entity.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the entity.
	 */
	Ogre::Real get_production_cooldown(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the current spawning progress (in seconds, not %).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the building.
	 * Param: The new spawning progress time.
	 * Note: Time amounts above the cooldown will be adjusted to match
	 *       the cooldown which will result into instant spawn.
	 */
	void set_production_progress(EntitySystem&, std::size_t, Ogre::Real);

	/**
	 * Brief: Returns the current spawning progress (in seconds, not %).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the building.
	 */
	Ogre::Real get_production_progress(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the amount of entities spawned by a given building,
	 *        but does not spawn or delete entities to match this number(!).
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the building.
	 * Param: The new entity spawned amount.
	 */
	void set_production_count(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the amount of entities spawned by a given building
	 *        that are still alive.
	 * Param: Reference to the entity system containing components.
	 * Param: ID of the building.
	 */
	std::size_t get_production_count(EntitySystem&, std::size_t);
}