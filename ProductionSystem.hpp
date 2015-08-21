#pragma once

#include <Ogre.h>

#include <string>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "GridSystem.hpp"

/**
 * System taking care of entities spawned by buildings and the spawn counts
 * allowing for a constant amount of entities (related to the number of buildings
 * spawning entities of that blueprint table).
 */
class ProductionSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's entity system.
		 * Param: Reference to the game's grid system (spawn positioning).
		 */
		ProductionSystem(EntitySystem&, GridSystem&);

		/**
		 * Destructor.
		 */
		~ProductionSystem() {}

		/**
		 * Brief: Iterates over all buildings and when possible, spawns new entities.
		 * Param: Time since last frame.
		 */
		void update(Ogre::Real) override;

		/**
		 * Brief: Spawns a single entity created by a building.
		 * Param: ID of the building.
		 * Param: Name of the blueprint table of the spawned entity.
		 */
		void spawn_entity(std::size_t, const std::string&);

		/**
		 * Brief: Changes the name of the blueprint table used to
		 *        spawn new entities.
		 * Param: ID of the building.
		 * Param: Name of the new building table.
		 */
		void set_production_blueprint(std::size_t, const std::string&);

		/**
		 * Brief: Returns the name of the blueprint table used to
		 *        spawn new entities.
		 * Param: ID of the building.
		 */
		const std::string& get_production_blueprint(std::size_t);

		/**
		 * Brief: Sets the maximal number of entities a given building
		 *        can spawn.
		 * Param: ID of the building.
		 * Param: The new entity limit.
		 */
		void set_production_limit(std::size_t, std::size_t);

		/**
		 * Brief: Returns the maximal number of entities a given building
		 *        can spawn.
		 * Param: ID of the building.
		 */
		std::size_t get_production_limit(std::size_t);
		
		/**
		 * Brief: Sets the time it takes for a given building to spawn
		 *        a single entity.
		 * Param: ID of the building.
		 * Param: The new entity spawning time.
		 */
		void set_production_cooldown(std::size_t, Ogre::Real);

		/**
		 * Brief: Returns the time it takes for a given building to spawn
		 *        a single entity.
		 * Param: ID of the entity.
		 */
		Ogre::Real get_production_cooldown(std::size_t);

		/**
		 * Brief: Sets the current spawning progress (in seconds, not %).
		 * Param: ID of the building.
		 * Param: The new spawning progress time.
		 * Note: Time amounts above the cooldown will be adjusted to match
		 *       the cooldown which will result into instant spawn.
		 */
		void set_production_progress(std::size_t, Ogre::Real);

		/**
		 * Brief: Returns the current spawning progress (in seconds, not %).
		 * Param: ID of the building.
		 */
		Ogre::Real get_production_progress(std::size_t);

		/**
		 * Brief: Sets the amount of entities spawned by a given building,
		 *        but does not spawn or delete entities to match this number(!).
		 * Param: ID of the building.
		 * Param: The new entity spawned amount.
		 */
		void set_production_count(std::size_t, std::size_t);

		/**
		 * Brief: Returns the amount of entities spawned by a given building
		 *        that are still alive.
		 * Param: ID of the building.
		 */
		std::size_t get_production_count(std::size_t);

		/**
		 * Brief: Set's the producer of a given entity (the building that
		 *        spawned it).
		 * Param: ID of the entity.
		 * Param: ID of the producer.
		 */
		void set_producer(std::size_t, std::size_t);

		/**
		 * Brief: Returns the producer of a given entity.
		 * Param: ID of the entity.
		 */
		std::size_t get_producer(std::size_t);
	private:
		/**
		 * Reference to the game's entity system (component retrieval).
		 */
		EntitySystem& entities_;

		/**
		 * Reference to the game's grid system (spawn positioning).
		 */
		GridSystem& grid_;

		/**
		 *
		 */
		std::string error_blueprint_;
};