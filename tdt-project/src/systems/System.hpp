#pragma once

#include <Typedefs.hpp>

/**
 * Parent class of all systems.
 */
class System
{
	public:
		/**
		 * \brief Updates the system.
		 * \param Time since the last frame.
		 */
		virtual void update(tdt::real) = 0;

		/**
		 * Destructor.
		 */
		virtual ~System() = default;
};