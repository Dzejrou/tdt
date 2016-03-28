#include "TimeSystem.hpp"
#include "EntitySystem.hpp"
#include "Helpers.hpp"
#include "lppscript/LppScript.hpp"
#include "Components.hpp"

TimeSystem::TimeSystem(EntitySystem& ents)
	: entities_{ents}, time_multiplier_{1.f}
{ /* DUMMY BODY */ }

void TimeSystem::update(tdt::real delta)
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

void TimeSystem::advance_all_timers(tdt::real delta)
{ // Note: Timers refers only to TimeComponents, ignore the others.
	for(auto& ent : entities_.get_component_container<TimeComponent>())
		ent.second.curr_time += delta;
}

void TimeSystem::advance_all_timers_of_type(tdt::real delta, TIME_EVENT type)
{
	for(auto& ent : entities_.get_component_container<TimeComponent>())
	{
		if(ent.second.event_type == type)
			ent.second.curr_time += delta;
	}
}

void TimeSystem::set_time_multiplier(tdt::real val)
{
	time_multiplier_ = val;
}

tdt::real TimeSystem::get_time_multiplier()
{
	return time_multiplier_;
}

void TimeSystem::handle_event_(tdt::uint id, TimeComponent& comp)
{
	switch(comp.event_type)
	{
		case TIME_EVENT::START_EVENT:
			EventHelper::set_active(entities_, comp.target, true);
			break;
		case TIME_EVENT::END_EVENT:
			DestructorHelper::destroy(entities_, comp.target);
			break;
		case TIME_EVENT::CALL_FUNCTION:
			lpp::Script::instance().call<void, tdt::uint>(NameHelper::get_name(entities_, id), id);
			break;
	}
	DestructorHelper::destroy(entities_, id);
}
