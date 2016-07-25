#pragma once

#include <string>
#include <Typedefs.hpp>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of the
 * production component.
 */
namespace ProductionHelper
{
	/**
	 * \brief Changes the name of the blueprint table used to
	 *        spawn new entities.
	 * \param Reference to the entity system containing components.
	 * \param ID of the building.
	 * \param Name of the new building table.
	 */
	void set_production_blueprint(EntitySystem&, tdt::uint, const std::string&);

	/**
	 * \brief Returns the name of the blueprint table used to
	 *        spawn new entities.
	 * \param Reference to the entity system containing components.
	 * \param ID of the building.
	 */
	const std::string& get_production_blueprint(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the maximal number of entities a given building
	 *        can spawn.
	 * \param Reference to the entity system containing components.
	 * \param ID of the building.
	 * \param The new entity limit.
	 */
	void set_production_limit(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the maximal number of entities a given building
	 *        can spawn.
	 * \param Reference to the entity system containing components.
	 * \param ID of the building.
	 */
	tdt::uint get_production_limit(EntitySystem&, tdt::uint);
	
	/**
	 * \brief Sets the time it takes for a given building to spawn
	 *        a single entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the building.
	 * \param The new entity spawning time.
	 */
	void set_production_cooldown(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the time it takes for a given building to spawn
	 *        a single entity.
	 * \param Reference to the entity system containing components.
	 * \param ID of the entity.
	 */
	tdt::real get_production_cooldown(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the current spawning progress (in seconds, not %).
	 * \param Reference to the entity system containing components.
	 * \param ID of the building.
	 * \param The new spawning progress time.
	 * \note Time amounts above the cooldown will be adjusted to match
	 *       the cooldown which will result into instant spawn.
	 */
	void set_production_progress(EntitySystem&, tdt::uint, tdt::real);

	/**
	 * \brief Returns the current spawning progress (in seconds, not %).
	 * \param Reference to the entity system containing components.
	 * \param ID of the building.
	 */
	tdt::real get_production_progress(EntitySystem&, tdt::uint);

	/**
	 * \brief Sets the amount of entities spawned by a given building,
	 *        but does not spawn or delete entities to match this number(!).
	 * \param Reference to the entity system containing components.
	 * \param ID of the building.
	 * \param The new entity spawned amount.
	 */
	void set_production_count(EntitySystem&, tdt::uint, tdt::uint);

	/**
	 * \brief Returns the amount of entities spawned by a given building
	 *        that are still alive.
	 * \param Reference to the entity system containing components.
	 * \param ID of the building.
	 */
	tdt::uint get_production_count(EntitySystem&, tdt::uint);
}