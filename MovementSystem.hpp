#pragma once

#include <Ogre.h>
#include <stdexcept>
#include <limits>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"

class MovementSystem : public System
{
	public:
		MovementSystem(EntitySystem&);
		~MovementSystem() {}

		void update(std::size_t, Ogre::Real);
		bool is_valid(std::size_t) const;
		bool is_moving(std::size_t) const;
		bool is_solid(std::size_t) const;
		bool can_move_to(std::size_t, Ogre::Vector3);
		bool move(std::size_t, Ogre::Vector3);
		void move_to(std::size_t, Ogre::Vector3);
		void rotate(std::size_t, Ogre::Real);
		const Ogre::AxisAlignedBox& get_bounds(std::size_t) const;
		bool collide(std::size_t, std::size_t) const;
		Ogre::Real get_distance(std::size_t, std::size_t) const;
		Ogre::Vector3 get_position(std::size_t) const;
		Ogre::Real get_speed_modifier(std::size_t) const;
		void set_speed_modifier(std::size_t, Ogre::Real);
		std::size_t enemy_in_radius(std::size_t, Ogre::Real) const;
		std::size_t closest_enemy(std::size_t) const;
		Ogre::Vector3 dir_to_closest_enemy(std::size_t, Ogre::Real = std::numeric_limits<Ogre::Real>::max()) const;
		Ogre::Vector3 dir_to_enemy(std::size_t, std::size_t) const;
	private:
		EntitySystem& entities_;
};