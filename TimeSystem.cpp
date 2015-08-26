#include "TimeSystem.hpp"

TimeSystem::TimeSystem(EntitySystem& ents)
	: entities_{ents}
{ /* DUMMY BODY */ }

void TimeSystem::update(Ogre::Real delta)
{
	for(auto& ent : entities_.get_component_container<TimeComponent>())
	{
		if(ent.second.curr_time < ent.second.time_limit)
			ent.second.curr_time += delta;
		else
		{
		
		}
	}
}

void TimeSystem::advance_all_timers(Ogre::Real delta)
{
	for(auto& ent : entities_.get_component_container<TimeComponent>())
		ent.second.curr_time += delta;
}

void TimeSystem::handle_event_(std::size_t id, TimeComponent& comp)
{
}
