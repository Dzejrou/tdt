#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "TimeHelper.hpp"

tdt::real TimeHelper::get_curr_time(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		return comp->curr_time;
	else
		return tdt::real{};
}

void TimeHelper::advance_curr_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		comp->curr_time += val;
}

void TimeHelper::max_curr_time(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		comp->curr_time = comp->time_limit;
}

void TimeHelper::set_time_limit(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		comp->time_limit = val;
}

tdt::real TimeHelper::get_time_limit(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		return comp->time_limit;
	else
		return tdt::real{};
}

void TimeHelper::set_target(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		comp->target = val;
}

tdt::uint TimeHelper::get_target(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		return comp->target;
	else
		return Component::NO_ENTITY;
}

void TimeHelper::set_type(EntitySystem& ents, tdt::uint id, TIME_EVENT val)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		comp->event_type = val;
}

TIME_EVENT TimeHelper::get_type(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		return comp->event_type;
	else
		return TIME_EVENT::NONE;
}