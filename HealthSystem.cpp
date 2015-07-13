#include "HealthSystem.hpp"

HealthSystem::HealthSystem(EntitySystem& ent)
	: entities_{ent}, regen_timer_{0}, regen_period_{1000} // TODO: Experiment with regen period!
{ /* DUMMY BODY */ }

void HealthSystem::update(Ogre::Real)
{
	bool regen{false};
	if(regen_timer_ > regen_period_)
	{
		regen = true;
		regen_timer_ = 0;
	}
	else
		++regen_timer_;

	auto& ents = entities_.get_component_list();
	for(auto it = ents.cbegin(); it != ents.cend(); ++it)
	{
		if(!entities_.get_component<HealthComponent>(it->first).alive)
		{ // Entity died.
			entities_.destroy_entity(it->first);
		}
		else if(regen)
			add_health(it->first, entities_.get_component<HealthComponent>(it->first).regen);
	}
}

bool HealthSystem::is_valid(std::size_t id)
{
	return entities_.has_component<HealthComponent>(id);
}

std::size_t HealthSystem::get_health(std::size_t id)
{
	if(is_valid(id))
		return entities_.get_component<HealthComponent>(id).curr_hp;
	else
		return 0;
}

void HealthSystem::add_health(std::size_t id, std::size_t val)
{
	if(is_valid(id))
	{
		auto& comp = entities_.get_component<HealthComponent>(id);
		std::size_t curr = comp.curr_hp;
		std::size_t max = comp.max_hp;

		if(curr + val > max)
			val = max - curr;
		comp.curr_hp += val;
	}
}

void HealthSystem::sub_health(std::size_t id, std::size_t val, bool ignore_defense)
{
	if(is_valid(id))
	{
		auto& comp = entities_.get_component<HealthComponent>(id);

		if(!ignore_defense)
			val -= comp.defense;

		if(comp.curr_hp <= val)
		{
			comp.curr_hp = 0;
			comp.alive = false;
		}
		else
			comp.curr_hp -= val;

	}
}

void HealthSystem::heal(std::size_t id)
{
	if(is_valid(id))
	{
		auto& comp = entities_.get_component<HealthComponent>(id);
		comp.curr_hp = comp.max_hp;
	}
}

void HealthSystem::buff(std::size_t id, std::size_t val)
{
	if(is_valid(id))
	{
		auto& comp = entities_.get_component<HealthComponent>(id);
		comp.curr_hp += val;
		comp.max_hp += val;
	}
}

std::size_t HealthSystem::get_defense(std::size_t id)
{
	if(is_valid(id))
		return entities_.get_component<HealthComponent>(id).defense;
	else
		return 0;
}

void HealthSystem::add_defense(std::size_t id, std::size_t val)
{
	if(is_valid(id))
		entities_.get_component<HealthComponent>(id).defense += val;
}

void HealthSystem::sub_defense(std::size_t id, std::size_t val)
{
	if(is_valid(id))
	{
		auto& comp = entities_.get_component<HealthComponent>(id);
		if(comp.defense - val < 0)
			comp.defense = 0;
		else
			comp.defense -= val;
	}
}
