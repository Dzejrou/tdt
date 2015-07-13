#pragma once

#include <Ogre.h>
#include <exception>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

class MovementSystem : public System
{
	public:
		MovementSystem(EntitySystem&);
		~MovementSystem() {}

		void update(Ogre::Real);
		bool is_valid(std::size_t) const;
		bool is_moving(std::size_t) const;
		bool is_solid(std::size_t) const;
		bool can_move_to(std::size_t, Ogre::Vector3);
		bool move(std::size_t, Ogre::Vector3);
		void move_to(std::size_t, Ogre::Vector3);
		const Ogre::AxisAlignedBox& get_bounds(std::size_t) const;
	private:
		EntitySystem& entities_;
};