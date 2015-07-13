#include "HealthSystem.hpp"

HealthSystem::HealthSystem(EntitySystem& ent)
	: entities_{ent}
{ /* DUMMY BODY */ }

void HealthSystem::update(Ogre::Real)
{
	const auto& ents = entities_.get_component_list();
	for(auto it = ents.cbegin(); it != ents.cend(); ++it)
	{
		if(!entities_.get_component<HealthComponent>(it->first).alive)
		{ // Entity died.
			entities_.destroy_entity(it->first);
		}
		else // TODO: Account for frame time! (Change health to float? Keep timer?)
			add_health(it->first, entities_.get_component<HealthComponent>(it->first).regen);
	}
}

std::size_t HealthSystem::get_health(std::size_t id)
{
	if(entities_.has_component<HealthComponent>(id))
		return entities_.get_component<HealthComponent>(id).curr_hp;
	else
		return 0;
}

void HealthSystem::add_health(std::size_t id, std::size_t val)
{
	if(entities_.has_component<HealthComponent>(id))
	{
		auto& comp = entities_.get_component<HealthComponent>(id);
		std::size_t curr = comp.curr_hp;
		std::size_t max = comp.max_hp;

		if(curr + val > max)
			val = max - curr;
		comp.curr_hp += val;
	}
}

void HealthSystem::sub_health(std::size_t id, std::size_t val)
{
	if(entities_.has_component<HealthComponent>(id))
	{
		auto& comp = entities_.get_component<HealthComponent>(id);
		if(comp.curr_hp <= val)
		{
			comp.curr_hp = 0;
			comp.alive = false;
		}
		else
			comp.curr_hp -= val;

	}
}