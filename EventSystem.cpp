#include "EventSystem.hpp"

EventSystem::EventSystem(EntitySystem& ents)
	: entities_{ents}, update_period_{1.f}, curr_update_time_{0.f}
{ /* DUMMY BODY */ }

void EventSystem::update(Ogre::Real delta)
{
	if(curr_update_time_ < update_period_)
	{
		curr_update_time_ += delta * update_time_multiplier_;
		return;
	}
	else
		curr_update_time_ = 0.f;

	for(auto& evt : entities_.get_component_container<EventComponent>())
	{
		if(!evt.second.active)
			continue;
		
		auto radius = evt.second.radius;
		if(radius == 0.f)
		{ // Targeted events.
			auto handler = entities_.get_component<EventHandlerComponent>(evt.second.target);
			if(handler && handler->possible_events.test((int)evt.second.event_type))
				handle_event_(evt.second.target, evt.first);
		}
		else
		{ // Area events.
			radius *= radius; // get_distance returns squared distance.
			
			for(auto& handler : entities_.get_component_container<EventHandlerComponent>())
			{
				if(handler.second.possible_events.test((int)evt.second.event_type)
				   && PhysicsHelper::get_distance(entities_, evt.first, handler.first) <= radius
				   && handle_event_(handler.first, evt.first))
				{
					break;
				}
			}
		}
	}
}

void EventSystem::set_update_period(Ogre::Real val)
{
	update_period_ = val;
}

Ogre::Real EventSystem::get_update_period() const
{
	return update_period_;
}

void EventSystem::set_update_time_multiplier(Ogre::Real val)
{
	update_time_multiplier_ = val;
}

Ogre::Real EventSystem::get_update_time_multiplier() const
{
	return update_time_multiplier_;
}

bool EventSystem::handle_event_(std::size_t handler, std::size_t evt)
{
	auto type = EventHelper::get_event_type(entities_, evt);
	switch(type)
	{
		case EVENT_TYPE::NONE:
			return true;
		case EVENT_TYPE::KILL_ENTITY:
			entities_.destroy_entity(handler);
			return true;
		default:
			return lpp::Script::get_singleton().call<bool, std::size_t, std::size_t>(
				EventHandlerHelper::get_handler(entities_, handler) + ".handle_event",
				handler, evt
			);
	}
}