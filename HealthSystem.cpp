#include "HealthSystem.hpp"

HealthSystem::HealthSystem(EntitySystem& ent)
	: entities_{ent}, regen_timer_{0.f}, regen_period_{10.f},
	  regen_{false}
{ /* DUMMY BODY */ }

void HealthSystem::update(Ogre::Real delta)
{
	update_regen(delta);
	for(auto& ent : entities_.get_component_container<HealthComponent>())
	{
		if(!ent.second.alive)
			DestructorHelper::destroy(entities_, ent.first);
		else if(regen_)
			HealthHelper::add_health(entities_, ent.first, ent.second.regen);
	}
}

void HealthSystem::update_regen(Ogre::Real delta)
{
	if(regen_)
	{
		regen_ = false;
	}
	else if(regen_timer_ > regen_period_)
	{
		regen_ = true;
		regen_timer_ = 0;
	}
	else
		regen_timer_ += delta;
}

void HealthSystem::set_regen_period(Ogre::Real val)
{
	regen_period_ = val;
}

Ogre::Real HealthSystem::get_regen_period() const
{
	return regen_period_;
}
