#pragma once

#include <Ogre.h>

class System
{
	public:
		virtual void update(Ogre::Real) = 0;
};