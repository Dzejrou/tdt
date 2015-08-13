#include "CombatSystem.hpp"

CombatSystem::CombatSystem(EntitySystem& ents, HealthSystem& health)
	: entities_{ents}, health_{health}, helper_box_{},
	  rd_device_{}, rd_gen_{rd_device_()}, rd_dist_{0, std::numeric_limits<std::size_t>::max()}
{ /* DUMMY BODY */ }

void CombatSystem::update(Ogre::Real delta)
{
	// Autoattacks.
	for(auto& ent : entities_.get_component_container<CombatComponent>())
	{
		if(ent.second.curr_target != Component::NO_ENTITY)
		{
			if(ent.second.cd_time < ent.second.cooldown)
			{
				ent.second.cd_time += delta;
				continue;
			}
			else
				ent.second.cd_time = 0;

			auto phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
			auto target_phys_comp = entities_.get_component<PhysicsComponent>(ent.second.curr_target);

			if(phys_comp && target_phys_comp &&
			   phys_comp->position.distance(target_phys_comp->position) < ent.second.range)
			{
				auto dmg = get_dmg(ent.second.min_dmg, ent.second.max_dmg);
				switch(ent.second.atk_type)
				{
					case ATTACK_TYPE::MELEE:
						health_.sub_health(ent.second.curr_target, dmg);
						// TODO: Animation...
						break;
					case ATTACK_TYPE::RANGED:
						// TODO: Spawn a projectile. (Homing component? :D)
						break;
				}
			}
			else // Target killed or ran away.
				ent.second.curr_target = Component::NO_ENTITY;
		}
	}

	// TODO: Spells.
}

void CombatSystem::set_range(std::size_t id, Ogre::Real range)
{
	auto comp = entities_.get_component<CombatComponent>(id);
	if(comp)
		comp->range = range;
}

Ogre::Real CombatSystem::get_range(std::size_t id) const
{
	auto comp = entities_.get_component<CombatComponent>(id);
	if(comp)
		return comp->range;
	else
		return 0;
}

void CombatSystem::set_dmg_range(std::size_t id, std::size_t min, std::size_t max)
{
	auto comp = entities_.get_component<CombatComponent>(id);
	if(comp)
	{
		comp->min_dmg = min;
		comp->max_dmg = max;
	}
}

std::tuple<std::size_t, std::size_t> CombatSystem::get_dmg_range(std::size_t id) const
{
	auto comp = entities_.get_component<CombatComponent>(id);
	if(comp)
		return std::make_tuple(comp->min_dmg, comp->max_dmg);
	else
		return std::tuple<std::size_t, std::size_t>{};
}

std::size_t CombatSystem::get_dmg(std::size_t min, std::size_t max)
{
	return rd_dist_(rd_gen_) % max + min;
}

void CombatSystem::set_cooldown(std::size_t id, Ogre::Real cd)
{
	auto comp = entities_.get_component<CombatComponent>(id);
	if(comp)
		comp->cooldown = cd;
}

Ogre::Real CombatSystem::get_cooldown(std::size_t id) const
{
	auto comp = entities_.get_component<CombatComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return 0;
}

void CombatSystem::set_atk_type(std::size_t id, ATTACK_TYPE type)
{
	auto comp = entities_.get_component<CombatComponent>(id);
	if(comp)
		comp->atk_type = type;
}

ATTACK_TYPE CombatSystem::get_atk_type(std::size_t id) const
{
	auto comp = entities_.get_component<CombatComponent>(id);
	if(comp)
		return comp->atk_type;
	else
		return ATTACK_TYPE::NONE;
}
