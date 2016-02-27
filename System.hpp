#pragma once

#include <Ogre.h>

/**
 * Parent class of all systems.
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
		virtual ~System() = default;
};