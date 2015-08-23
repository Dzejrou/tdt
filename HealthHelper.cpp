#include "HealthHelper.hpp"

void HealthHelper::set_health(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
	{
		if(val == 0)
			comp->alive = false;
		comp->curr_hp = val;
	}
}

std::size_t HealthHelper::get_health(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
		return comp->curr_hp;
	else
		return std::size_t{};
}

void HealthHelper::add_health(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
		comp->curr_hp = (comp->curr_hp + val >= comp->max_hp ? comp->max_hp : comp->curr_hp + val);
}

void HealthHelper::sub_health(EntitySystem& ents, std::size_t id, std::size_t val, bool ignore_armor)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
	{
		if(!ignore_armor)
			val = (comp->defense < val ? val - comp->defense : 0);

		if(comp->curr_hp <= val)
		{
			comp->curr_hp = 0;
			comp->alive = false;
		}
		else
			comp->curr_hp -= val;
	}
}

void HealthHelper::heal(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
		comp->curr_hp = comp->max_hp;
}

void HealthHelper::buff(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
	{
		comp->max_hp += val;
		comp->curr_hp += val;
	}
}

void HealthHelper::debuff(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
	{
		if(comp->curr_hp <= val)
		{
			comp->curr_hp = 1;
			comp->max_hp = 1;
		}
		else
		{
			comp->max_hp -= val;
			comp->curr_hp -= val;
		}
	}
}

void HealthHelper::set_regen(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
		comp->regen = val;
}

std::size_t HealthHelper::get_regen(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
		return comp->regen;
	else
		return std::size_t{};
}

void HealthHelper::set_alive(EntitySystem& ents, std::size_t id, bool val)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
		comp->alive = val;
}

bool HealthHelper::is_alive(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
		return comp->alive;
	else
		return false;
}

void HealthHelper::set_defense(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
		comp->defense = val;
}

std::size_t HealthHelper::get_defense(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
		return comp->defense;
	else
		return std::size_t{};
}

void HealthHelper::add_defense(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
		comp->defense += val;
}

void HealthHelper::sub_defense(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
	{
		if(comp->defense < val)
			comp->defense = 0;
		else
			comp->defense -= val;
	}
}

void HealthHelper::ubercharge(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<HealthComponent>(id);
	if(comp)
	{ // Note: Component::NO_ENTITY should be typedef'd to the maximal value of size_t.
		comp->curr_hp = Component::NO_ENTITY;
		comp->max_hp = Component::NO_ENTITY;
		comp->defense = Component::NO_ENTITY;
	}
}
