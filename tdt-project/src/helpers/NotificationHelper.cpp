#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <gui/GUI.hpp>
#include "NotificationHelper.hpp"

static tdt::cache::NotificationCache cache{Component::NO_ENTITY, nullptr};

void NotificationHelper::set_cooldown(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	NotificationComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, NotificationComponent);
	if(comp)
		comp->cooldown = val;
}

tdt::real NotificationHelper::get_cooldown(EntitySystem& ents, tdt::uint id)
{
	NotificationComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, NotificationComponent);
	if(comp)
		return comp->cooldown;
	else
		return tdt::real{};
}

void NotificationHelper::reset(EntitySystem& ents, tdt::uint id)
{
	NotificationComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, NotificationComponent);
	if(comp)
		comp->curr_time = comp->cooldown;
}

bool NotificationHelper::notify(EntitySystem& ents, tdt::uint id, const std::string& msg)
{
	NotificationComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, NotificationComponent);
	if(comp && comp->curr_time >= comp->cooldown)
	{
		GUI::instance().get_log().print("\\[#" + std::to_string(id) + "\\] " + msg);
		comp->curr_time = 0.f;
		return true;
	}
	else
		return false;
}

tdt::real NotificationHelper::get_curr_time(EntitySystem& ents, tdt::uint id)
{
	NotificationComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, NotificationComponent);
	if(comp)
		return comp->curr_time;
	else
		return tdt::real{};
}

void NotificationHelper::advance_curr_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	NotificationComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, NotificationComponent);
	if(comp) // Negative values intentionally allowed for cooldown prolonging.
		comp->curr_time += val;
}
