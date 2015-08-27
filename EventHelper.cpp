#include "EventHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void EventHelper::set_event_type(EntitySystem& ents, std::size_t id, EVENT_TYPE val)
{
	auto comp = ents.get_component<EventComponent>(id);
	if(comp)
		comp->event_type = val;
}

EVENT_TYPE EventHelper::get_event_type(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<EventComponent>(id);
	if(comp)
		return comp->event_type;
	else
		return EVENT_TYPE::NONE;
}

void EventHelper::set_target(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<EventComponent>(id);
	if(comp)
		comp->target = val;
}

std::size_t EventHelper::get_target(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<EventComponent>(id);
	if(comp)
		return comp->target;
	else
		return Component::NO_ENTITY;
}

void EventHelper::set_radius(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<EventComponent>(id);
	if(comp)
		comp->radius = val;
}

Ogre::Real EventHelper::get_radius(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<EventComponent>(id);
	if(comp)
		return comp->radius;
	else
		return Ogre::Real{};
}

void EventHelper::set_active(EntitySystem& ents, std::size_t id, bool val)
{
	auto comp = ents.get_component<EventComponent>(id);
	if(comp)
		comp->active = val;
}

bool EventHelper::is_active(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<EventComponent>(id);
	if(comp)
		return comp->active;
	else
		return false;
}
