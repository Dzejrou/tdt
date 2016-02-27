#include "TimeSystem.hpp"

TimeSystem::TimeSystem(EntitySystem& ents)
	: entities_{ents}, time_multiplier_{1.f}
{ /* DUMMY BODY */ }

void TimeSystem::update(Ogre::Real delta)
{
	for(auto& ent : entities_.get_component_container<TimeComponent>())
	{
		if(ent.second.curr_time < ent.second.time_limit)
			ent.second.curr_time += delta * time_multiplier_;
		else
			handle_event_(ent.first, ent.second);
	}

	for(auto& ent : entities_.get_component_container<OnHitComponent>())
	{
		if(ent.second.curr_time < ent.second.cooldown)
			ent.second.curr_time += delta * time_multiplier_;
	}

	for(auto& ent : entities_.get_component_container<TriggerComponent>())
	{
		if(ent.second.curr_time < ent.second.cooldown)
			ent.second.curr_time += delta * time_multiplier_;
	}

	for(auto& ent : entities_.get_component_container<NotificationComponent>())
	{
		if(ent.second.curr_time < ent.second.cooldown)
			ent.second.curr_time += delta * time_multiplier_;
	}

	for(auto& ent : entities_.get_component_container<LimitedLifeSpanComponent>())
	{
		if(ent.second.curr_time < ent.second.max_time)
			ent.second.curr_time += delta * time_multiplier_;
		else
			DestructorHelper::destroy(entities_, ent.first);
	}
}

void TimeSystem::advance_all_timers(Ogre::Real delta)
{ // Note: Timers refers only to TimeComponents, ignore the others.
	for(auto& ent : entities_.get_component_container<TimeComponent>())
		ent.second.curr_time += delta;
}

void TimeSystem::advance_all_timers_of_type(Ogre::Real delta, TIME_EVENT type)
{
	for(auto& ent : entities_.get_component_container<TimeComponent>())
	{
		if(ent.second.event_type == type)
			ent.second.curr_time += delta;
	}
}

void TimeSystem::set_time_multiplier(Ogre::Real val)
{
	time_multiplier_ = val;
}

Ogre::Real TimeSystem::get_time_multiplier()
{
	return time_multiplier_;
}

void TimeSystem::handle_event_(std::size_t id, TimeComponent& comp)
{
	switch(comp.event_type)
	{
		case TIME_EVENT::START_EVENT:
			EventHelper::set_active(entities_, comp.target, true);
			break;
		case TIME_EVENT::END_EVENT:
			DestructorHelper::destroy(entities_, comp.target);
			break;
	}
	DestructorHelper::destroy(entities_, id);
}
