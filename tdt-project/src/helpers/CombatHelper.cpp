#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <tools/Util.hpp>
#include <random>
#include <numeric>
#include "CombatHelper.hpp"

static tdt::cache::CombatCache cache{Component::NO_ENTITY, nullptr};

void CombatHelper::set_target(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
		comp->curr_target = val;
}

tdt::uint CombatHelper::get_target(EntitySystem& ents, tdt::uint id)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
		return comp->curr_target;
	else
		return Component::NO_ENTITY;
}

void CombatHelper::set_range(EntitySystem& ents, tdt::uint id, tdt::real range)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
		comp->range = range;
}

tdt::real CombatHelper::get_range(EntitySystem& ents, tdt::uint id)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
		return comp->range;
	else
		return 0;
}

void CombatHelper::set_dmg_range(EntitySystem& ents, tdt::uint id, tdt::uint min, tdt::uint max)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
	{
		comp->min_dmg = min;
		comp->max_dmg = max;
	}
}

std::tuple<tdt::uint, tdt::uint> CombatHelper::get_dmg_range(EntitySystem& ents, tdt::uint id)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
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
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
		comp->cooldown = cd;
}

tdt::real CombatHelper::get_cooldown(EntitySystem& ents, tdt::uint id)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
		return comp->cooldown;
	else
		return 0;
}

void CombatHelper::set_atk_type(EntitySystem& ents, tdt::uint id, ATTACK_TYPE type)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
		comp->atk_type = type;
}

ATTACK_TYPE CombatHelper::get_atk_type(EntitySystem& ents, tdt::uint id)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
		return comp->atk_type;
	else
		return ATTACK_TYPE::NONE;
}

bool CombatHelper::in_range(EntitySystem& ents, tdt::uint id1, tdt::uint id2)
{
	auto phys1 = ents.get_component<PhysicsComponent>(id1);
	auto phys2 = ents.get_component<PhysicsComponent>(id2);

	CombatComponent* comb{nullptr};
	GET_COMPONENT(id1, ents, comb, CombatComponent);

	if(phys1 && phys2 && comb)
		return phys1->position.squaredDistance(phys2->position) <= comb->range * comb->range;
	else
		return false;
}

void CombatHelper::set_projectile_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
		comp->projectile_blueprint = val;
}

const std::string& CombatHelper::get_projectile_blueprint(EntitySystem& ents, tdt::uint id)
{
	CombatComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CombatComponent);
	if(comp)
		return comp->projectile_blueprint;
	else
		return ents.NO_BLUEPRINT;
}
