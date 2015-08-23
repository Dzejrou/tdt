#pragma once

#include <Ogre.h>

#include <random>
#include <tuple>
#include <numeric>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "HealthSystem.hpp"
#include "MovementSystem.hpp"
#include "HealthHelper.hpp"
#include "CombatHelper.hpp"

/**
 * Manages auto attack melee and ranged combat, special melee and ranged attacks will be
 * both handled by the spellcasting system.
 */
class CombatSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's entity system (component retrieval).
		 * Param: Reference to the game's health system (damage dealing).
		 * Param: Reference to the main scene manager (ray casting).
		 * Param: Reference to the movement system (model orientation when attacking).
		 */
		CombatSystem(EntitySystem&, HealthSystem&, Ogre::SceneManager&, MovementSystem&);

		/**
		 * Destructor.
		 */
		~CombatSystem() {}

		/**
		 * Brief: Updates all auto attack combat in the game currently in progress.
		 * Param: Time since the last frame.
		 */
		void update(Ogre::Real) override;

		/**
		 * Brief: Returns true if two given entities can see each other,
		 *        false otherwise.
		 * Param: ID of the first entity.
		 * Param: ID of the second entity.
		 * NOTE: Tests only if entities that have query flags of WALL or BUILDING
		 *       are in the way, allows to see through other friendly/enemy/neutral
		 *       entities.
		 */
		bool in_sight(std::size_t, std::size_t) const;

		/**
		 * Brief: Changes the target of a given entity representing a homing
		 *        projectile.
		 * Param: ID of the entity.
		 * Param: ID of the target.
		 * TODO: Getters.
		 */
		void set_homing_source(std::size_t, std::size_t);

		/**
		 * Brief: Changes the source (the caster) of a given entity representing
		 *        a homing projectile.
		 * Param: ID of the entity.
		 * Param: ID of the source.
		 * TODO: Getters.
		 */
		void set_homing_target(std::size_t, std::size_t);

		/**
		 * Brief: Changes the damage of a ggiven entity representing a homing
		 *        projectile.
		 * Param: ID of the entity.
		 * Param: The new damage value.
		 * TODO: Getters.
		 */
		void set_homing_dmg(std::size_t, std::size_t);

		/**
		 * Brief: Returns the ID of the closest entity (from a given entity's
		 *        position), Component::NO_ENTITY otherwise.
		 * Param: ID of the entity from whose position the search is performed.
		 * Param: If true, will return only entities in sight.
		 * Param: If true, will return only friendly entities (enemies otherwise).
		 */
		std::size_t get_closest_entity(std::size_t,bool = true, bool = false) const;
	private:
		/**
		 * Brief: Creates a new homing projectile at the position of a given entity
		 *        homing at the entity's current target.
		 * Param: ID of the caster entity.
		 * Param: Reference to the caster entity's combat component.
		 */
		void create_homing_projectile(std::size_t, CombatComponent&);

		/**
		 * Reference to the game's entity system (component retrieval).
		 */
		EntitySystem& entities_;

		/**
		 * Reference to the game's health system (damage dealing).
		 */
		HealthSystem& health_;

		/**
		 * Reference to the game's movement system (model transformation).
		 */
		MovementSystem& movement_;

		/**
		 * Set of tools from the c++11 stdlib used to calculate
		 * pseudo random numbers.
		 */
		std::random_device rd_device_;
		std::uniform_int_distribution<std::size_t> rd_dist_;
		std::mt19937 rd_gen_;

		/**
		 * Reference to the ray cast used to check if two entities can see each other.
		 */
		Ogre::RaySceneQuery& ray_query_;
};