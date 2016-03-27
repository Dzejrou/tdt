#pragma once

#include <OgrePrerequisites.h>
#include <cstdlib>

/**
 * Namespace containing numeric types used in the game.
 * TODO: Change the use of std::size_t and Ogre::Real to tdt:uint and tdt:real.
 */
namespace tdt
{
	using uint = std::size_t;
	using real = Ogre::Real;

#if OGRE_DOUBLE_PRECISION == 0
#	define REAL_ZERO 0.f
#else
#	define REAL_ZERO 0.0
#endif
}
