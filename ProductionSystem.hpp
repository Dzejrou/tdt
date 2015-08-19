#pragma once

#include <Ogre.h>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "GridSystem.hpp"

class ProductionSystem : public System
{
	public:
		ProductionSystem(EntitySystem&, GridSystem&);
		~ProductionSystem() {}

		void update(Ogre::Real) override;
	private:
		EntitySystem& entities_;
		GridSystem& grid_;
};