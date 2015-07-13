#pragma once

#include "System.hpp"
#include "EntitySystem.hpp"

class HealthSystem : public System
{
	public:
		HealthSystem(EntitySystem&);

		void update(Ogre::Real);
		std::size_t get_health(std::size_t);
		void add_health(std::size_t, std::size_t);
		void sub_health(std::size_t, std::size_t);
	public:
		EntitySystem& entities_;
};