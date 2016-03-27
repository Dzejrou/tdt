#include "EventHandlerHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void EventHandlerHelper::set_handler(EntitySystem& ents, std::size_t id, const std::string& val)
{
	auto comp = ents.get_component<EventHandlerComponent>(id);
	if(comp)
		comp->handler = val;
}

const std::string & EventHandlerHelper::get_handler(EntitySystem& ents, std::size_t id)
{
	static std::string NO_HANDLER{"ERROR"};

	auto comp = ents.get_component<EventHandlerComponent>(id);
	if(comp)
		return comp->handler;
	else
		return NO_HANDLER;
}

bool EventHandlerHelper::can_handle(EntitySystem& ents, std::size_t id, EVENT_TYPE val)
{
	auto comp = ents.get_component<EventHandlerComponent>(id);
	if(comp)
		return comp->possible_events.test((std::size_t)val);
	else
		return false;
}

void EventHandlerHelper::add_possible_event(EntitySystem& ents, std::size_t id, EVENT_TYPE val)
{
	auto comp = ents.get_component<EventHandlerComponent>(id);
	if(comp)
		comp->possible_events.set((std::size_t)val);
}

void EventHandlerHelper::delete_possible_event(EntitySystem& ents, std::size_t id, EVENT_TYPE val)
{
	auto comp = ents.get_component<EventHandlerComponent>(id);
	if(comp)
		comp->possible_events.set((std::size_t)val, false);
}
