#pragma once

#include <Ogre.h>

#include <random>
#include <tuple>
#include <numeric>

#include "System.hpp"
#include "EntitySystem.hpp"
#include "HealthSystem.hpp"

class CombatSystem : public System
{
	public:
		CombatSystem(EntitySystem&, HealthSystem&);
		~CombatSystem() {}

		void update(Ogre::Real) override;

		void set_range(std::size_t, Ogre::Real);
		Ogre::Real get_range(std::size_t) const;

		void set_dmg_range(std::size_t, std::size_t, std::size_t);
		std::tuple<std::size_t, std::size_t> get_dmg_range(std::size_t) const;

		std::size_t get_dmg(std::size_t, std::size_t);

		void set_cooldown(std::size_t, Ogre::Real);
		Ogre::Real get_cooldown(std::size_t) const;

		void set_atk_type(std::size_t, ATTACK_TYPE);
		ATTACK_TYPE get_atk_type(std::size_t) const;
	private:
		void create_homing_projectile(std::size_t, CombatComponent&);

		EntitySystem& entities_;
		HealthSystem& health_;

		Ogre::AxisAlignedBox helper_box_;

		std::random_device rd_device_;
		std::uniform_int_distribution<std::size_t> rd_dist_;
		std::mt19937 rd_gen_;
};