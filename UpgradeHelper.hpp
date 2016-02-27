#pragma once

#include <cstdlib>
#include <string>
class EntitySystem;

/**
 * Auxiliary namespace containing functions that help with the management of
 * the upgrade component.
 */
namespace UpgradeHelper
{
	/**
	 * Brief: Sets the blueprint table that handles the upgrading of
	 *        a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new blueprint name.
	 */
	void set_blueprint(EntitySystem&, std::size_t, const std::string&);

	/**
	 * Brief: Returns the blueprint table that handles the upgrading of
	 *        a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	const std::string& get_blueprint(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the amount of experience a given entity has. Won't allow
	 *        more experience than is needed for the next level and returns the
	 *        remaining experience not added.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new experience amount.
	 */
	std::size_t set_experience(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the amount of experience a given entity has.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get_experience(EntitySystem&, std::size_t);

	/**
	 * Brief: Adds a given amount of experience to a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The amount of experience to be added.
	 */
	std::size_t add_experience(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Sets the amount of experience needed for next level of a
	 *        given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new experience amount needed.
	 */
	void set_exp_needed(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the amount of experience needed for next level of a
	 *        given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get_exp_needed(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the level of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new level.
	 * Note: Does not change the attributes of the entity!
	 */
	void set_level(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the level of a given entity.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get_level(EntitySystem&, std::size_t);

	/**
	 * Brief: Sets the maximum level a given entity can reach.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 * Param: The new max level.
	 */
	void set_level_cap(EntitySystem&, std::size_t, std::size_t);

	/**
	 * Brief: Returns the maximum level a given entity can reach.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	std::size_t get_level_cap(EntitySystem&, std::size_t);

	/**
	 * Brief: Returns true if a given entity can level up.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	bool can_level_up(EntitySystem&, std::size_t);

	/**
	 * Brief: Upgrades a given entity that can level up.
	 * Param: Entity system containing the entity.
	 * Param: ID of the entity.
	 */
	void upgrade(EntitySystem&, std::size_t);
}