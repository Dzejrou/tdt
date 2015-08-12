#include "CombatSystem.hpp"

CombatSystem::CombatSystem(EntitySystem& ents, HealthSystem& health)
	: entities_{ents}, health_{health}, helper_box_{},
	rd_device_{}, rd_gen_{rd_device_}, rd_dist_{std::numeric_limits<std::size_t>::max()}
{ /* DUMMY BODY */ }

void CombatSystem::update(Ogre::Real)
{
}

void CombatSystem::set_range(std::size_t id, std::size_t range)
{
	auto comp = entities_.get_component<CombatComponent>(id);
	if(comp)
		comp->range = range;
}

std::size_t CombatSystem::get_range(std::size_t id) const
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
