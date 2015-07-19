#pragma once

#include <Ogre.h>

/**
 * Parent class of all systems (except for EntitySystem, which does not have any form of updating).
 */
class System
{
	public:
		/**
		 * Brief: Updates a valid entity.
		 * Param: ID of the entity.
		 * Param: Time since the last frame.
		 */
		virtual void update(std::size_t, Ogre::Real) = 0;

		/**
		 * Brief: Returns true if an entity is valid, false otherwise.
		 * Param: ID of the entity.
		 */
		virtual bool is_valid(std::size_t) const = 0;

		/**
		 * Destructor.
		 */
		virtual ~System() {}
};