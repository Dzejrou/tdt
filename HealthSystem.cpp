#include "HealthSystem.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "HealthHelper.hpp"

HealthSystem::HealthSystem(EntitySystem& ent)
	: entities_{ent}, regen_timer_{}, regen_period_{10.f},
	  regen_{false}
{ /* DUMMY BODY */ }

void HealthSystem::update(tdt::real delta)
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

void HealthSystem::update_regen(tdt::real delta)
{
	if(regen_)
	{
		regen_ = false;
	}
	else if(regen_timer_ > regen_period_)
	{
		regen_ = true;
		regen_timer_ = REAL_ZERO;
	}
	else
		regen_timer_ += delta;
}

void HealthSystem::set_regen_period(tdt::real val)
{
	regen_period_ = val;
}

tdt::real HealthSystem::get_regen_period() const
{
	return regen_period_;
}
