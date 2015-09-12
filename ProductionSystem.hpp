#pragma once

#include <Ogre.h>
#include <string>
#include <cstdlib>
#include "System.hpp"
#include "EntitySystem.hpp"
#include "Grid.hpp"
#include "Helpers.hpp"

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
		 */
		ProductionSystem(EntitySystem&);

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
		 * Brief: Sets the time value by which the frame times are multiplied
		 *        when added to the production timers.
		 * Param: The new time multiplier.
		 */
		void set_time_multiplier(Ogre::Real);

		/**
		 * Brief: Returns the time value by which the frame times are multiplied
		 *        when added to the production timers.
		 */
		Ogre::Real get_time_multiplier();
	private:
		/**
		 * Reference to the game's entity system (component retrieval).
		 */
		EntitySystem& entities_;

		/**
		 * Reference to the game's pathfinding grid (spawn positioning).
		 */
		Grid& grid_;

		/**
		 * Allows to speed up/slow down the production of all buildings.
		 */
		Ogre::Real time_multiplier_;
};