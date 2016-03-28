#include "CombatHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "Util.hpp"
#include <random>
#include <numeric>

void CombatHelper::set_target(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		comp->curr_target = val;
}

tdt::uint CombatHelper::get_target(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return comp->curr_target;
	else
		return Component::NO_ENTITY;
}

void CombatHelper::set_range(EntitySystem& ents, tdt::uint id, tdt::real range)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		comp->range = range;
}

tdt::real CombatHelper::get_range(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return comp->range;
	else
		return 0;
}

void CombatHelper::set_dmg_range(EntitySystem& ents, tdt::uint id, tdt::uint min, tdt::uint max)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
	{
		comp->min_dmg = min;
		comp->max_dmg = max;
	}
}

std::tuple<tdt::uint, tdt::uint> CombatHelper::get_dmg_range(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return std::make_tuple(comp->min_dmg, comp->max_dmg);
	else
		return std::tuple<tdt::uint, tdt::uint>{};
}

tdt::uint CombatHelper::get_dmg(tdt::uint min, tdt::uint max)
{
	return util::get_random(min, max);
}

void CombatHelper::set_cooldown(EntitySystem& ents, tdt::uint id, tdt::real cd)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		comp->cooldown = cd;
}

tdt::real CombatHelper::get_cooldown(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return 0;
}

void CombatHelper::set_atk_type(EntitySystem& ents, tdt::uint id, ATTACK_TYPE type)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		comp->atk_type = type;
}

ATTACK_TYPE CombatHelper::get_atk_type(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return comp->atk_type;
	else
		return ATTACK_TYPE::NONE;
}

bool CombatHelper::in_range(EntitySystem& ents, tdt::uint id1, tdt::uint id2)
{
	auto phys1 = ents.get_component<PhysicsComponent>(id1);
	auto phys2 = ents.get_component<PhysicsComponent>(id2);
	auto comb = ents.get_component<CombatComponent>(id1);

	if(phys1 && phys2 && comb)
		return phys1->position.squaredDistance(phys2->position) <= comb->range * comb->range;
	else
		return false;
}

void CombatHelper::set_projectile_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		comp->projectile_blueprint = val;
}

const std::string& CombatHelper::get_projectile_blueprint(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<CombatComponent>(id);
	if(comp)
		return comp->projectile_blueprint;
	else
		return ents.NO_BLUEPRINT;
}
