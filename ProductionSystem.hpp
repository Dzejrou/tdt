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

		void set_production_blueprint(std::size_t, const std::string&);
		const std::string& get_production_blueprint(std::size_t);
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