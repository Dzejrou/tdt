#include "HealthSystem.hpp"

HealthSystem::HealthSystem(EntitySystem& ent)
	: entities_{ent}, regen_timer_{0}, regen_period_{1000} // TODO: Experiment with regen period!
{ /* DUMMY BODY */ }

void HealthSystem::update(Ogre::Real)
{
	update_regen();
	for(auto& ent : entities_.get_component_container<HealthComponent>())
	{
		if(!ent.second.alive)
		{ // Entity died.
			entities_.destroy_entity(ent.first);
		}
		else if(regen_)
			add_health(ent.first, ent.second.regen);
	}
}

bool HealthSystem::is_valid(std::size_t id) const
{
	return entities_.has_component<HealthComponent>(id);
}

void HealthSystem::update_regen()
{
	if(regen_)
	{
		regen_ = false;
		return;
	}

	if(regen_timer_ > regen_period_)
	{
		regen_ = true;
		regen_timer_ = 0;
	}
	else
		++regen_timer_;
}

std::size_t HealthSystem::get_health(std::size_t id) const
{
	auto comp = entities_.get_component<HealthComponent>(id);
	if(comp)
		return comp->curr_hp;
	else
		return 0;
}

void HealthSystem::add_health(std::size_t id, std::size_t val)
{
	auto comp = entities_.get_component<HealthComponent>(id);
	if(comp)
	{
		std::size_t curr = comp->curr_hp;
		std::size_t max = comp->max_hp;

		if(curr + val > max)
			val = max - curr;
		comp->curr_hp += val;
	}
}

void HealthSystem::sub_health(std::size_t id, std::size_t val, bool ignore_defense)
{
	auto comp = entities_.get_component<HealthComponent>(id);
	if(comp)
	{
		if(!ignore_defense)
			val -= comp->defense;

		if(comp->curr_hp <= val)
		{
			comp->curr_hp = 0;
			comp->alive = false;
		}
		else
			comp->curr_hp -= val;

	}
}

void HealthSystem::heal(std::size_t id)
{
	auto comp = entities_.get_component<HealthComponent>(id);
	if(comp)
		comp->curr_hp = comp->max_hp;
}

void HealthSystem::buff(std::size_t id, std::size_t val)
{
	auto comp = entities_.get_component<HealthComponent>(id);
	if(comp)
	{
		comp->curr_hp += val;
		comp->max_hp += val;
	}
}

void HealthSystem::set_regen(std::size_t id, std::size_t regen)
{
	auto comp = entities_.get_component<HealthComponent>(id);
	if(comp)
		comp->regen = regen;
}

void HealthSystem::set_alive(std::size_t id, bool alive)
{
	auto comp = entities_.get_component<HealthComponent>(id);
	if(comp)
		comp->alive = alive;
}

std::size_t HealthSystem::get_defense(std::size_t id) const
{
	auto comp = entities_.get_component<HealthComponent>(id);
	if(comp)
		return comp->defense;
	else
		return 0;
}

void HealthSystem::add_defense(std::size_t id, std::size_t val)
{
	auto comp = entities_.get_component<HealthComponent>(id);
	if(comp)
		comp->defense += val;
}

void HealthSystem::sub_defense(std::size_t id, std::size_t val)
{
	auto comp = entities_.get_component<HealthComponent>(id);
	if(comp)
	{
		if(comp->defense - val < 0)
			comp->defense = 0;
		else
			comp->defense -= val;
	}
}
