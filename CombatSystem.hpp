#pragma once

#include <Ogre.h>

#include <random>
#include <tuple>
#include <numeric>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "HealthSystem.hpp"
#include "MovementSystem.hpp"

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
		 * Brief: Changes the attack range of a given entity.
		 * Param: ID of the entity.
		 * Param: The new attack range.
		 */
		void set_range(std::size_t, Ogre::Real);

		/**
		 * Brief: Returns the attack range of a given entity.
		 * Param: ID of the entity.
		 */
		Ogre::Real get_range(std::size_t) const;

		/**
		 * Brief: Changes the damage range (min damage, max damage) that a given
		 *        entity can deal when attacking.
		 * Param: ID of the entity.
		 * Param: Minimal damage value.
		 * Param: Maximal damage value.
		 */
		void set_dmg_range(std::size_t, std::size_t, std::size_t);

		/**
		 * Brief: Returns the damage range (in the form of a 2-member tuple) of
		 *        a given entity.
		 * Param: ID of the entity.
		 */
		std::tuple<std::size_t, std::size_t> get_dmg_range(std::size_t) const;

		/**
		 * Brief: Returns a pseudo random damage value between given two numbers,
		 *        used to calculate the damage of each individual attack.
		 * Param: Minimal damage value.
		 * Param: Maximal damage value.
		 */
		std::size_t get_dmg(std::size_t, std::size_t);

		/**
		 * Brief: Changes the cooldown (minimal time between attacks) of a given entity.
		 * Param: ID of the entity.
		 * Param: The new cooldown value.
		 */
		void set_cooldown(std::size_t, Ogre::Real);

		/**
		 * Brief: Returns the cooldown (minimal time between attacks) of a given entity.
		 * Param: ID of the entity.
		 */
		Ogre::Real get_cooldown(std::size_t) const;

		/**
		 * Brief: Changes the attack type of a given entity.
		 * Param: ID of the entity.
		 * Param: The new attack type.
		 */
		void set_atk_type(std::size_t, ATTACK_TYPE);

		/**
		 * Brief: Returns the attack type of a given entity.
		 * Param: ID of the entity.
		 */
		ATTACK_TYPE get_atk_type(std::size_t) const;

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

		// TODO: Getters.
		/**
		 * Brief: Changes the target of a given entity representing a homing
		 *        projectile.
		 * Param: ID of the entity.
		 * Param: ID of the target.
		 */
		void set_homing_source(std::size_t, std::size_t);

		/**
		 * Brief: Changes the source (the caster) of a given entity representing
		 *        a homing projectile.
		 * Param: ID of the entity.
		 * Param: ID of the source.
		 */
		void set_homing_target(std::size_t, std::size_t);

		/**
		 * Brief: Changes the damage of a ggiven entity representing a homing
		 *        projectile.
		 * Param: ID of the entity.
		 * Param: The new damage value.
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