#include "ManaCrystalHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "Player.hpp"

void ManaCrystalHelper::set_capacity(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<ManaCrystalComponent>(id);
	if(comp)
	{
		if(comp->cap_increase < val)
			Player::instance().add_max_mana(val - comp->cap_increase);
		else
			Player::instance().sub_max_mana(comp->cap_increase - val);
		comp->cap_increase = val;
	}
}

std::size_t ManaCrystalHelper::get_capacity(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ManaCrystalComponent>(id);
	if(comp)
		return comp->cap_increase;
	else
		return std::size_t();
}

void ManaCrystalHelper::set_regen(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<ManaCrystalComponent>(id);
	if(comp)
	{
		if(comp->regen_increase < val)
			Player::instance().add_mana_regen(val - comp->regen_increase);
		else
			Player::instance().sub_mana_regen(comp->regen_increase - val);
		comp->regen_increase = val;
	}
}

std::size_t ManaCrystalHelper::get_regen(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ManaCrystalComponent>(id);
	if(comp)
		return comp->regen_increase;
	else
		return std::size_t();
}
