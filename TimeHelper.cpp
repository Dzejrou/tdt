#include "TimeHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

Ogre::Real TimeHelper::get_curr_time(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		return comp->curr_time;
	else
		return Ogre::Real{};
}

void TimeHelper::advance_curr_time(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		comp->curr_time += val;
}

void TimeHelper::max_curr_time(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		comp->curr_time = comp->time_limit;
}

void TimeHelper::set_time_limit(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		comp->time_limit = val;
}

Ogre::Real TimeHelper::get_time_limit(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		return comp->time_limit;
	else
		return Ogre::Real{};
}

void TimeHelper::set_target(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		comp->target = val;
}

std::size_t TimeHelper::get_target(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		return comp->target;
	else
		return Component::NO_ENTITY;
}

void TimeHelper::set_type(EntitySystem& ents, std::size_t id, TIME_EVENT val)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		comp->event_type = val;
}

TIME_EVENT TimeHelper::get_type(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TimeComponent>(id);
	if(comp)
		return comp->event_type;
	else
		return TIME_EVENT::NONE;
}