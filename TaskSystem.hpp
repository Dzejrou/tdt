#pragma once

#include <set>

#include "System.hpp"
#include "EntitySystem.hpp"

class TaskSystem : public System
{
	public:
		TaskSystem(EntitySystem&);
		~TaskSystem() {}

		void update(Ogre::Real);
	private:
		EntitySystem& entities_;
};