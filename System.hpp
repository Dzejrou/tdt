#pragma once

#include "Typedefs.hpp"

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
		virtual void update(tdt::real) = 0;

		/**
		 * Destructor.
		 */
		virtual ~System() = default;
};