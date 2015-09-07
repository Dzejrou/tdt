#include "CombatHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void CombatHelper::set_target(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		comp->curr_target = val;
}

std::size_t CombatHelper::get_combat_target(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return comp->curr_target;
	else
		return Component::NO_ENTITY;
}

void CombatHelper::set_range(EntitySystem& ents, std::size_t id, Ogre::Real range)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		comp->range = range;
}

Ogre::Real CombatHelper::get_range(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return comp->range;
	else
		return 0;
}

void CombatHelper::set_dmg_range(EntitySystem& ents, std::size_t id, std::size_t min, std::size_t max)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
	{
		comp->min_dmg = min;
		comp->max_dmg = max;
	}
}

std::tuple<std::size_t, std::size_t> CombatHelper::get_dmg_range(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return std::make_tuple(comp->min_dmg, comp->max_dmg);
	else
		return std::tuple<std::size_t, std::size_t>{};
}

std::size_t CombatHelper::get_dmg(std::size_t min, std::size_t max)
{
	return std::uniform_int_distribution<std::size_t>{0, std::numeric_limits<std::size_t>::max()}(
		   std::mt19937{std::random_device{}()}) % max + min;
}

void CombatHelper::set_cooldown(EntitySystem& ents, std::size_t id, Ogre::Real cd)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		comp->cooldown = cd;
}

Ogre::Real CombatHelper::get_cooldown(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return 0;
}

void CombatHelper::set_atk_type(EntitySystem& ents, std::size_t id, ATTACK_TYPE type)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		comp->atk_type = type;
}

ATTACK_TYPE CombatHelper::get_atk_type(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return comp->atk_type;
	else
		return ATTACK_TYPE::NONE;
}