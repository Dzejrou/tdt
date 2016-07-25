#include <helpers/Helpers.hpp>
#include <gui/GUI.hpp>
#include "TriggerSystem.hpp"
#include "EntitySystem.hpp"

TriggerSystem::TriggerSystem(EntitySystem& ents)
	: entities_{ents}, check_timer_{}, check_period_{1.f}
{ /* DUMMY BODY */ }

void TriggerSystem::update(tdt::real delta)
{
	if(check_timer_ < check_period_)
		check_timer_ += delta;
	else
	{
		check_timer_ = REAL_ZERO;
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
							if(entities_.has_component<StructureComponent>(other.first))
								continue;
							if(phys_comp->position.squaredDistance(other.second.position) < ent.second.radius * ent.second.radius)
							{
								TriggerHelper::trigger(entities_, ent.first, other.first);
								ent.second.curr_time = REAL_ZERO;
							}
						}
						break;
					case FACTION::FRIENDLY: // Trigger only the opposite faction.
					case FACTION::ENEMY:
						for(auto& other : entities_.get_component_container<FactionComponent>())
						{
							if(entities_.has_component<StructureComponent>(other.first))
								continue;
							if(faction != FactionHelper::get_faction(entities_, other.first)
							   && PhysicsHelper::get_distance(entities_, ent.first, other.first) < ent.second.radius * ent.second.radius)
							{
								TriggerHelper::trigger(entities_, ent.first, other.first);
								ent.second.curr_time = REAL_ZERO;
							}
						}
						break;
				}
			}
		}
	}
}

void TriggerSystem::set_check_period(tdt::real val)
{
	check_period_ = val;
}

tdt::real TriggerSystem::get_check_period() const
{
	return check_period_;
}
