#pragma once

#include <Ogre.h>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

class HealthSystem : public System
{
	public:
		HealthSystem(EntitySystem&);
		~HealthSystem() {}

		void update(std::size_t, Ogre::Real);
		bool is_valid(std::size_t) const;
		void update_regen();
		std::size_t get_health(std::size_t) const;
		void add_health(std::size_t, std::size_t);
		void sub_health(std::size_t, std::size_t, bool = false);
		void heal(std::size_t);
		void buff(std::size_t, std::size_t);

		std::size_t get_defense(std::size_t) const;
		void add_defense(std::size_t, std::size_t);
		void sub_defense(std::size_t, std::size_t);
	public:
		EntitySystem& entities_;
		std::size_t regen_timer_;
		std::size_t regen_period_;
		bool regen_;
};