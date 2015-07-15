#pragma once

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "lppscript\LppScript.hpp"

class AISystem : public System
{
	public:
		AISystem(EntitySystem&);
		~AISystem() {}

		void update(Ogre::Real);
		bool is_valid(std::size_t) const;
		bool is_friendly(std::size_t, std::size_t) const;
	private:
		EntitySystem& entities_;
};