#include "TriggerSystem.hpp"
#include "Helpers.hpp"

TriggerSystem::TriggerSystem(EntitySystem& ents)
	: entities_{ents}, check_timer_{}, check_period_{1.f}
{ /* DUMMY BODY */ }

void TriggerSystem::update(Ogre::Real delta)
{
	if(check_timer_ < check_period_)
		check_timer_ += delta;
	else
	{
		check_timer_ = 0;
		for(auto& ent : entities_.get_component_container<TriggerComponent>())
		{
			if(ent.second.curr_time >= ent.second.cooldown)
			{
				auto phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
				if(!phys_comp)
					continue;

				FACTION faction = FactionHelper::get_faction(entities_, ent.first);
				switch(faction)
				{
					case FACTION::NEUTRAL: // Trigger with both factions.
						for(auto& other : entities_.get_component_container<PhysicsComponent>())
						{
							if(faction == FactionHelper::get_faction(entities_, other.first)
							   && phys_comp->position.squaredDistance(other.second.position) < ent.second.radius * ent.second.radius)
							{
								TriggerHelper::trigger(entities_, ent.first, other.first);
								ent.second.curr_time = 0.f;
							}
						
						}
						break;
					case FACTION::FRIENDLY: // Trigger only same faction.
					case FACTION::ENEMY:
						for(auto& other : entities_.get_component_container<FactionComponent>())
						{
							if(faction == FactionHelper::get_faction(entities_, other.first)
							   && PhysicsHelper::get_distance(entities_, ent.first, other.first) < ent.second.radius * ent.second.radius)
							{
								TriggerHelper::trigger(entities_, ent.first, other.first);
								ent.second.curr_time = 0.f;
							}
						}
						break;
				}
			}
		}
	}
}

void TriggerSystem::set_check_period(Ogre::Real val)
{
	check_period_ = val;
}

Ogre::Real TriggerSystem::get_check_period() const
{
	return check_period_;
}
