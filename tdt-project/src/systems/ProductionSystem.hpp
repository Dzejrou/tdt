#pragma once

#include <string>
#include <Typedefs.hpp>
#include "System.hpp"
class EntitySystem;
class Grid;

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
		 * \param Reference to the game's entity system.
		 */
		ProductionSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~ProductionSystem() {}

		/**
		 * \brief Iterates over all buildings and when possible, spawns new entities.
		 * \param Time since last frame.
		 */
		void update(tdt::real) override;

		/**
		 * \brief Spawns a single entity created by a building.
		 * \param ID of the building.
		 * \param Name of the blueprint table of the spawned entity.
		 */
		void spawn_entity(tdt::uint, const std::string&);

		/**
		 * \brief Sets the time value by which the frame times are multiplied
		 *        when added to the production timers.
		 * \param The new time multiplier.
		 */
		void set_time_multiplier(tdt::real);

		/**
		 * \brief Returns the time value by which the frame times are multiplied
		 *        when added to the production timers.
		 */
		tdt::real get_time_multiplier();

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
		tdt::real time_multiplier_;
};