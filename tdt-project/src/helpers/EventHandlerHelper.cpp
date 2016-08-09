#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "EventHandlerHelper.hpp"

static tdt::cache::EventHandlerCache cache{Component::NO_ENTITY, nullptr};

void EventHandlerHelper::set_handler(EntitySystem& ents, std::size_t id, const std::string& val)
{
	EventHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventHandlerComponent);
	if(comp)
		comp->handler = val;
}

const std::string & EventHandlerHelper::get_handler(EntitySystem& ents, std::size_t id)
{
	EventHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventHandlerComponent);
	if(comp)
		return comp->handler;
	else
		return ents.NO_BLUEPRINT;
}

bool EventHandlerHelper::can_handle(EntitySystem& ents, std::size_t id, EVENT_TYPE val)
{
	EventHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventHandlerComponent);
	if(comp)
		return comp->possible_events.test((std::size_t)val);
	else
		return false;
}

void EventHandlerHelper::add_possible_event(EntitySystem& ents, std::size_t id, EVENT_TYPE val)
{
	EventHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventHandlerComponent);
	if(comp)
		comp->possible_events.set((std::size_t)val);
}

void EventHandlerHelper::delete_possible_event(EntitySystem& ents, std::size_t id, EVENT_TYPE val)
{
	EventHandlerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, EventHandlerComponent);
	if(comp)
		comp->possible_events.set((std::size_t)val, false);
}
