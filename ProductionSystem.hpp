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
};