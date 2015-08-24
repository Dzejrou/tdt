#pragma once

#include <Ogre.h>
#include <stdexcept>
#include <limits>
#include <cstdlib>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "PhysicsHelper.hpp"
#include "GraphicsHelper.hpp"
#include "MovementHelper.hpp"

/**
 * System handling movement related updates and containing movement & physics related methods.
 */
class MovementSystem : public System
{
	public:
		/**
		 * Constructor.
		 * Param: Reference to the game's entity system.
		 */
		MovementSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~MovementSystem() {}

		/**
		 * Brief: Updates the movement system.
		 * Param: Time since the last frame.
		 */
		void update(Ogre::Real);

		/**
		 * Brief: Returns true if a given entity can move to a given point in space, false otherwise.
		 * Param: ID of the entity.
		 * Param: Target coordinate.
		 */
		bool can_move_to(std::size_t, Ogre::Vector3);

		/**
		 * Brief: Sets a given entity to move in a given direction, returns true if such movement is possible and
		 *        false otherwise. The move will then be applied in the update method.
		 * Param: ID of the entity.
		 * Param: Directional vector.
		 * Note: Every vector passed to this method should be normalised and the length of the move will be
		 *       increased by the entity's speed modifier. This is not enforced though.
		 */
		bool move(std::size_t, Ogre::Vector3);
	private:
		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;
};