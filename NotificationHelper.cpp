#include "NotificationHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "GUI.hpp"

void NotificationHelper::set_cooldown(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp)
		comp->cooldown = val;
}

Ogre::Real NotificationHelper::get_cooldown(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return Ogre::Real{};
}

void NotificationHelper::reset(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp)
		comp->curr_time = comp->cooldown;
}

bool NotificationHelper::notify(EntitySystem& ents, std::size_t id, const std::string& msg)
{
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp && comp->curr_time >= comp->cooldown)
	{
		GUI::instance().get_log().print("\\[" + std::to_string(id) + "\\] " + msg);
		comp->curr_time = 0.f;
		return true;
	}
	else
		return false;
}

Ogre::Real NotificationHelper::get_curr_time(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp)
		return comp->curr_time;
	else
		return Ogre::Real{};
}

void NotificationHelper::advance_curr_time(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp) // Negative values intentionally allow for cooldown prolonging.
		comp->curr_time += val;
}
