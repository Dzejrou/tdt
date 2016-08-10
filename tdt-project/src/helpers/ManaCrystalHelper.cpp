#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <tools/Player.hpp>
#include "ManaCrystalHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::ManaCrystalCache cache{Component::NO_ENTITY, nullptr};
#endif

void ManaCrystalHelper::set_capacity(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	ManaCrystalComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaCrystalComponent);
	if(comp)
	{
		if(comp->cap_increase < val)
			Player::instance().add_max_mana(val - comp->cap_increase);
		else
			Player::instance().sub_max_mana(comp->cap_increase - val);
		comp->cap_increase = val;
	}
}

tdt::uint ManaCrystalHelper::get_capacity(EntitySystem& ents, tdt::uint id)
{
	ManaCrystalComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaCrystalComponent);
	if(comp)
		return comp->cap_increase;
	else
		return tdt::uint();
}

void ManaCrystalHelper::set_regen(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	ManaCrystalComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaCrystalComponent);
	if(comp)
	{
		if(comp->regen_increase < val)
			Player::instance().add_mana_regen(val - comp->regen_increase);
		else
			Player::instance().sub_mana_regen(comp->regen_increase - val);
		comp->regen_increase = val;
	}
}

tdt::uint ManaCrystalHelper::get_regen(EntitySystem& ents, tdt::uint id)
{
	ManaCrystalComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaCrystalComponent);
	if(comp)
		return comp->regen_increase;
	else
		return tdt::uint();
}
