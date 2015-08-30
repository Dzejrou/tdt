#include "HealthSystem.hpp"

HealthSystem::HealthSystem(EntitySystem& ent)
	: entities_{ent}, regen_timer_{0}, regen_period_{1000.f} // TODO: Time period in a config!
{ /* DUMMY BODY */ }

void HealthSystem::update(Ogre::Real delta)
{
	update_regen(delta);
	for(auto& ent : entities_.get_component_container<HealthComponent>())
	{
		if(!ent.second.alive)
		{
			auto product_component = entities_.get_component<ProductComponent>(ent.first);
			if(product_component)
			{
				auto production_component = entities_.get_component<ProductionComponent>(
					product_component->producer
				);
				if(production_component && production_component->curr_produced > 0)
					--production_component->curr_produced;
			}

			DestructorHelper::destroy(entities_, ent.first);
		}
		else if(regen_)
			HealthHelper::add_health(entities_, ent.first, ent.second.regen);
	}
}

void HealthSystem::update_regen(Ogre::Real delta)
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
