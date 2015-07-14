#pragma once

#include <Ogre.h>

class System
{
	public:
		virtual void update(Ogre::Real) = 0;
		virtual bool is_valid(std::size_t) const = 0;
		virtual ~System() {}
};