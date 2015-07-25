#pragma once

#include <Ogre.h>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

class GridSystem : public System
{
	public:
		GridSystem(EntitySystem&);
		~GridSystem() {}

		void update(Ogre::Real);
		bool is_valid(std::size_t);
	private:
		EntitySystem& entities_;
};