#pragma once

#include <Ogre.h>
#include <tuple>
#include <cstdlib>
#include "System.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "HealthHelper.hpp"
#include "CombatHelper.hpp"
#include "GraphicsHelper.hpp"
#include "GridSystem.hpp"
#include "Util.hpp"

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
		 * Param: Reference to the main scene manager (ray casting).
		 * Param: Reference to the game's grid system (accessibility).
		 */
		CombatSystem(EntitySystem&, Ogre::SceneManager&, GridSystem&);

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
		 * Brief: Returns the ID of the closest entity (from a given entity's
		 *        position), Component::NO_ENTITY otherwise.
		 * Param: ID of the entity from whose position the search is performed.
		 * Param: If true, will return only entities in sight.
		 * Param: If true, will return only friendly entities (enemies otherwise).
		 */
		std::size_t get_closest_entity(std::size_t,bool = true, bool = false) const;

		/**
		 * Brief: Returns the ID of the closest gold deposit (entity with both structure
		 *        and gold components).
		 * Param: ID of the entity that looks for the gold deposit.
		 * Param: If true, only deposits in sight will be checked.
		 */
		std::size_t get_closest_gold_deposit(std::size_t, bool = false) const;

		/**
		 * Brief: Returns the ID of the closest entity that has a given component, meets
		 *        a given condition and is accessible.
		 * Param: ID of the entity that is searching.
		 * Param: Functor representing the condition.
		 * Param: If true, only entities in sight get checked.
		 */
		template<typename COND>
		std::size_t get_closest_entity(std::size_t id, COND condition, bool only_sight = true) const
		{
			auto comp = entities_.get_component<COMP>(id);
			auto phys_comp = entities_.get_component<PhysicsComponent>(id);

			std::size_t closest_id = Component::NO_ENTITY;
			Ogre::Real min_distance = std::numeric_limits<Ogre::Real>::max();
			if(comp && phys_comp)
			{
				for(auto& ent : entities_.get_component_list())
				{
					if(ent.first == id || !condition(ent.first))
						continue;

					auto enemy_phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
					if(enemy_phys_comp)
					{
						auto dist = phys_comp->position.squaredDistance(enemy_phys_comp->position);
						if(enemy_phys_comp && dist < min_distance && (!only_sight || in_sight(id, ent.first))
						   && grid_.perform_a_star(id, ent.first, false))
						{
							min_distance = dist;
							closest_id = ent.first;
						}
					}
				}
			}
			return closest_id;
		}
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
		 * Reference to the ray cast used to check if two entities can see each other.
		 */
		Ogre::RaySceneQuery& ray_query_;

		/**
		 * Used to check if an entity is accessible.
		 */
		GridSystem& grid_;
};