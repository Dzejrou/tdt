#pragma once

#include <tuple>
#include <bitset>
#include <map>
#include <string>
#include <queue>
#include "System.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "Util.hpp"
#include "RayCaster.hpp"
class GridSystem;

/**
 * Used for entity container filtering, this represents the entity
 * component list. (Allows to iterate over all entities in the get entity
 * methods.)
 * Also contains functions used to apply negative/positive effects to entities
 * and finding an entity having given properties.
 */
using ALL_COMPONENTS = std::bitset<Component::count>;

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
		~CombatSystem() = default;

		/**
		 * Brief: Updates all auto attack combat in the game currently in progress.
		 * Param: Time since the last frame.
		 */
		void update(tdt::real) override;

		/**
		 * Brief: Returns true if two given entities can see each other,
		 *        false otherwise. Tests polygons.
		 * Param: ID of the first entity.
		 * Param: ID of the second entity.
		 * NOTE: Tests only if entities that have query flags of WALL or BUILDING
		 *       are in the way, allows to see through other friendly/enemy/neutral
		 *       entities.
		 */
		bool in_sight(tdt::uint, tdt::uint) const;

		/**
		 * Brief: Returns true if two given entities can see each other,
		 *        false otherwise. Tests only bounding boxes.
		 * Param: ID of the first entity.
		 * Param: ID of the second entity.
		 * NOTE: Tests only if entities that have query flags of WALL or BUILDING
		 *       are in the way, allows to see through other friendly/enemy/neutral
		 *       entities.
		 */
		bool in_sight_wrt_BB(tdt::uint, tdt::uint) const;

		/**
		 * Brief: Returns the ID of the closest entity (from a given entity's
		 *        position), Component::NO_ENTITY otherwise.
		 * Param: ID of the entity from whose position the search is performed.
		 * Param: If true, will return only entities in sight.
		 * Param: If true, will return only friendly entities (enemies otherwise).
		 */
		tdt::uint get_closest_entity(tdt::uint, bool = true, bool = false) const;

		/**
		 * Brief: Returns the ID of the closest structure (from a given entity's
		 *        position), Component::NO_ENTITY otherwise.
		 * Param: ID of the entity from whose position the search is performed.
		 * Param: If true, will return only structures in sight.
		 * Param: If true, will return friendly structures (enemies otherwise).
		 */
		tdt::uint get_closest_structure(tdt::uint, bool = true, bool = false) const;

		/**
		 * Brief: Returns the ID of the closest entity (from a given entity's
		 *        position) ignoring a given entity, Component::NO_ENTITY otherwise.
		 * Param: ID of the entity from whose position the search is performed.
		 * Param: ID of the entity that's ignored in the search.
		 * Param: If true, will return only entities in sight.
		 * Param: If true, will return only friendly entities (enemies otherwise).
		 */
		tdt::uint get_closest_entity_thats_not(tdt::uint, tdt::uint, bool = true, bool = false) const;

		/**
		 * Brief: Returns the ID of the closest gold deposit (entity with both structure
		 *        and gold components).
		 * Param: ID of the entity that looks for the gold deposit.
		 * Param: If true, only deposits in sight will be checked.
		 */
		tdt::uint get_closest_gold_deposit(tdt::uint, bool = false) const;

		/**
		 * Brief: Returns the ID of the closest gold vault that can store player's gold.
		 * Param: ID of the entity that looks for the gold vault.
		 * Param: If true, only vaults in sight will be checked.
		 * Param: If true, only vaults that have free space for more gold will be checked.
		 */
		tdt::uint get_closest_gold_vault(tdt::uint, bool = false, bool = false) const;

		/**
		 * Brief: Returns the ID of the closest entity that has a given component, meets
		 *        a given condition and is accessible.
		 * Param: ID of the entity that is searching.
		 * Param: Functor representing the condition.
		 * Param: If true, only entities in sight get checked.
		 * Note: The explicit template specialization determines over which component container
		 *       this method will iterate, use a component name for a specific components only
		 *       or ALL_COMPONENTS for the component bitset map (which allows to iterate over
		 *       all entitites regardless of their components).
		 */
		template<typename CONT, typename COND>
		tdt::uint get_closest_entity(tdt::uint id, COND& condition, bool only_sight = true) const
		{
			auto phys_comp = entities_.get_component<PhysicsComponent>(id);
			tdt::uint closest_id = Component::NO_ENTITY;
			tdt::real min_distance = std::numeric_limits<tdt::real>::max();
			if(phys_comp)
			{
				for(auto& ent : get_container<CONT>())
				{
					if(ent.first == id || !condition(ent.first))
						continue;

					auto enemy_phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
					if(enemy_phys_comp)
					{
						auto dist = phys_comp->position.squaredDistance(enemy_phys_comp->position);
						if(enemy_phys_comp && dist < min_distance && (!only_sight || in_sight(id, ent.first))
						   && util::pathfind(entities_, id, ent.first, util::DEFAULT_HEURISTIC{entities_}, false))
						{
							min_distance = dist;
							closest_id = ent.first;
						}
					}
				}
			}
			return closest_id;
		}

		/**
		 * Brief: Applies a given effect (functor given by the template argument EFFECT) to all
		 *        entities conforming the condition (functor given by the template argument COND)
		 *        in a given range from a given entity.
		 * Param: ID of the entity.
		 * Param: Instance of the condition functor.
		 * Param: Instance of the effect functor.
		 * Param: The radius.
		 * Note: The explicit template specialization determines over which component container
		 *       this method will iterate, use a component name for a specific components only
		 *       or ALL_COMPONENTS for the component bitset map (which allows to iterate over
		 *       all entitites regardless of their components).
		 */
		template<typename CONT, typename COND, typename EFFECT>
		void apply_effect_to_entities_in_range(tdt::uint id, COND& condition, EFFECT& effect, tdt::real range)
		{
			auto comp = entities_.get_component<PhysicsComponent>(id);
			if(comp)
			{
				Ogre::Vector2 pos{comp->position.x, comp->position.z};
				for(auto& ent : get_container<CONT>())
				{
					if(condition(ent.first) &&
					   pos.distance(PhysicsHelper::get_2d_position(entities_, ent.first)) < range)
					{ // Sqrt used in distance calculation should not be a bottleneck here.
						effect(ent.first);
					}
				}
			}
		}

		/**
		 * Brief: Heals all friendly entities within a given range from a given entity.
		 * Param: ID of the entity.
		 * Param: The range.
		 */
		void apply_heal_to_entities_in_range(tdt::uint, tdt::real);

		/**
		 * Brief: Damages all friendly entities within a given range from a given entity.
		 * Param: ID of the entity.
		 * Param: The range.
		 * Param: Minimal damage value.
		 * Param: Maximal damage value.
		 */
		void apply_damage_to_entities_in_range(tdt::uint, tdt::real, tdt::uint, tdt::uint);

		/**
		 * Brief: Slows all enemy entities within a given range from a given entity for a
		 *        given time period.
		 * Param: ID of the entity.
		 * Param: The range.
		 * Param: The time period for which the slow is active.
		 */
		void apply_slow_to_entities_in_range(tdt::uint, tdt::real, tdt::real);

		/**
		 * Brief: Freezes all enemy entities within a given range from a given entity for a
		 *        given time period.
		 * Param: ID of the entity.
		 * Param: The range.
		 * Param: The time period for which the freeze is active.
		 */
		void apply_freeze_to_entities_in_range(tdt::uint, tdt::real, tdt::real);

		/**
		 * Brief: Slows a given entity for a given time period.
		 * Param: ID of the entity.
		 * Param: The time period for which the freeze is active.
		 */
		void apply_slow_to(tdt::uint, tdt::real);

		/**
		 * Brief: Freezes a given entity for a given time period.
		 * Param: ID of the entity.
		 * Param: The time period for which the freeze is active.
		 */
		void apply_freeze_to(tdt::uint, tdt::real);

		/**
		 * Brief: Tries to find a path used by an entity to run away from another entity.
		 * Param: ID of the entity running away.
		 * Param: ID of the entity that is ran away from.
		 * Param: Minimal amount of nodes the path has to have (will be ignored if the amount
		 *        of attempts surpasses the maximum amount).
		 * Note: This is just a dummy that enqueues the entity for pathfinding.
		 */
		void run_away_from(tdt::uint, tdt::uint, tdt::uint);

		/**
		 * Brief: Sets the maximum amount of pathfinding attempts for running away.
		 * Param: The new maximum amount.
		 */
		void set_max_run_away_attempts(tdt::uint);

		/**
		 * Brief: Returns the maximum amount of pathfinding attempts for running away.
		 */
		tdt::uint get_max_run_away_attempts();

		/**
		 * Brief: Returns true if an enemy is in range from a given entity, false
		 *        otherwise.
		 * Param: ID of the entity.
		 */
		bool enemy_in_range(tdt::uint);

	private:
		/**
		 * Brief: Retuns a map containing pairs of IDs and components of a given type, use
		 *        the type ALL_COMPONENTS to get the <ID, component bitset> container.
		 */
		template<typename COMP>
		const std::map<tdt::uint, COMP>& get_container() const
		{
			return entities_.get_component_container<COMP>();
		}

		/**
		 * Brief: Creates a new homing projectile at the position of a given entity
		 *        homing at the entity's current target.
		 * Param: ID of the caster entity.
		 * Param: Reference to the caster entity's combat component.
		 */
		void create_homing_projectile(tdt::uint, CombatComponent&);

		/**
		 * Brief: Tries to find a path used by an entity to run away from another entity.
		 * Param: ID of the entity running away.
		 * Param: ID of the entity that is ran away from.
		 * Param: Minimal amount of nodes the path has to have (will be ignored if the amount
		 *        of attempts surpasses the maximum amount).
		 * Note: This is the actual implementation.
		 */
		void run_away_from_(tdt::uint, tdt::uint, tdt::uint);


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

		/**
		 * Used for polygon precise line of sight checking.
		 */
		RayCaster ray_caster_;

		/**
		 * Maximum amount of pathfindings performed when running away from an enemy.
		 */
		tdt::uint max_run_away_attempts_{10};

		/**
		 * Used to distribute run away pathfindings over frames (otherwise something
		 * like a meteor falling on a big group of entities would freeze the game until
		 * all run away pathfindings are done.)
		 */
		std::queue<std::tuple<tdt::uint, tdt::uint, tdt::uint>> run_away_queue_;
};

/**
 * Brief: Specific case of the get_container method, which returns the map containing
 *        <ID, component bitset> map containing all entities.
 */
template<>
inline const std::map<tdt::uint, ALL_COMPONENTS>& CombatSystem::get_container() const
{
	return entities_.get_component_list();
}