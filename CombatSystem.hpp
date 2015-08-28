#pragma once

#include <Ogre.h>

#include <tuple>
#include <cstdlib>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "HealthHelper.hpp"
#include "CombatHelper.hpp"
#include "GraphicsHelper.hpp"

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
		 */
		CombatSystem(EntitySystem&, Ogre::SceneManager&);

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
};