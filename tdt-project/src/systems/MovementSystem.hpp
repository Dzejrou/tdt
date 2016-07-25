#pragma once

#include <OGRE/Ogre.h>
#include "System.hpp"
class EntitySystem;

/**
 * System handling movement related updates and containing movement & physics related methods.
 */
class MovementSystem : public System
{
	public:
		/**
		 * Constructor.
		 * \param Reference to the game's entity system.
		 */
		MovementSystem(EntitySystem&);

		/**
		 * Destructor.
		 */
		~MovementSystem() {}

		/**
		 * \brief Updates the movement system.
		 * \param Time since the last frame.
		 */
		void update(Ogre::Real);

		/**
		 * \brief Returns true if a given entity can move to a given point in space, false otherwise.
		 * \param ID of the entity.
		 * \param Target coordinate.
		 */
		bool can_move_to(std::size_t, Ogre::Vector3);

		/**
		 * \brief Sets a given entity to move in a given direction, returns true if such movement is possible and
		 *        false otherwise. The move will then be applied in the update method.
		 * \param ID of the entity.
		 * \param Directional vector.
		 * \note Every vector passed to this method should be normalised and the length of the move will be
		 *       increased by the entity's speed modifier. This is not enforced though.
		 * \note Checks for collisions.
		 */
		bool checked_move(std::size_t, Ogre::Vector3);

		/**
		 * \brief Sets a given entity to move in a given direction, returns true if such movement is possible and
		 *        false otherwise. The move will then be applied in the update method.
		 * \param ID of the entity.
		 * \param Directional vector.
		 * \note Every vector passed to this method should be normalised and the length of the move will be
		 *       increased by the entity's speed modifier. This is not enforced though.
		 * \note Does not check for collisions.
		 */
		bool move(std::size_t, Ogre::Vector3);

	private:
		/**
		 * Reference to the game's entity system.
		 */
		EntitySystem& entities_;

		/**
		 * Time between the last frame and this frame, used so that lua calls to the move functions
		 * still use the time of this frame.
		 */
		Ogre::Real last_delta_;
};