#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "EventHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::EventCache cache{Component::NO_ENTITY, nullptr};
#endif

void EventHelper::set_event_type(EntitySystem& ents, std::size_t id, EVENT_TYPE val)
{
	EventComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventComponent);
	if(comp)
		comp->event_type = val;
}

EVENT_TYPE EventHelper::get_event_type(EntitySystem& ents, std::size_t id)
{
	EventComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventComponent);
	if(comp)
		return comp->event_type;
	else
		return EVENT_TYPE::NONE;
}

void EventHelper::set_target(EntitySystem& ents, std::size_t id, std::size_t val)
{
	EventComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventComponent);
	if(comp)
		comp->target = val;
}

std::size_t EventHelper::get_target(EntitySystem& ents, std::size_t id)
{
	EventComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventComponent);
	if(comp)
		return comp->target;
	else
		return Component::NO_ENTITY;
}

void EventHelper::set_radius(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	EventComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventComponent);
	if(comp)
		comp->radius = val;
}

Ogre::Real EventHelper::get_radius(EntitySystem& ents, std::size_t id)
{
	EventComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventComponent);
	if(comp)
		return comp->radius;
	else
		return 0.000001f;
}

void EventHelper::set_active(EntitySystem& ents, std::size_t id, bool val)
{
	EventComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventComponent);
	if(comp)
		comp->active = val;
}

bool EventHelper::is_active(EntitySystem& ents, std::size_t id)
{
	EventComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventComponent);
	if(comp)
		return comp->active;
	else
		return false;
}

void EventHelper::set_event_handler(EntitySystem& ents, std::size_t id, std::size_t val)
{
	EventComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventComponent);
	if(comp)
		comp->handler = val;
}

std::size_t EventHelper::get_event_handler(EntitySystem& ents, std::size_t id)
{
	EventComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventComponent);
	if(comp)
		return comp->handler;
	else
		return Component::NO_ENTITY;
}
