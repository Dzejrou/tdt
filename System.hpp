#pragma once

#include <Ogre.h>

/**
 * Parent class of all systems (except for EntitySystem, which does not have any form of updating).
 */
class System
{
	public:
		/**
		 * Brief: Updates the system.
		 * Param: Time since the last frame.
		 */
		virtual void update(Ogre::Real) = 0;

		/**
		 * Destructor.
		 */
		virtual ~System() {}
};