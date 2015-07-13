#pragma once

#include <Ogre.h>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

class MovementSystem : public System
{
	public:
		MovementSystem(EntitySystem&);
		~MovementSystem() {}

		void update(Ogre::Real);
		bool is_valid(std::size_t);
		bool can_move_to(std::size_t, Ogre::Vector3);
		void move(std::size_t, Ogre::Vector3);
		Ogre::AxisAlignedBox& get_bounds(std::size_t);
	private:
		EntitySystem& entities_;
};