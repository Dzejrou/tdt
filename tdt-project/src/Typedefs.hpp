#pragma once

#include <OGRE/OgrePrerequisites.h>
#include <cstdlib>

/**
 * Namespace containing numeric types used in the game.
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

/**
 * Some auxiliary macros and defines:
 */
#define DEFERRED_SHADING_ALLOWED 1
#define CACHE_ALLOWED 1
#define NO_SHADOWS 1