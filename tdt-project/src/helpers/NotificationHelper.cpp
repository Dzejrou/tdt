#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include <gui/GUI.hpp>
#include "NotificationHelper.hpp"

void NotificationHelper::set_cooldown(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp)
		comp->cooldown = val;
}

tdt::real NotificationHelper::get_cooldown(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return tdt::real{};
}

void NotificationHelper::reset(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp)
		comp->curr_time = comp->cooldown;
}

bool NotificationHelper::notify(EntitySystem& ents, tdt::uint id, const std::string& msg)
{
	auto comp = ents.get_component<NotificationComponent>(id);
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
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp)
		return comp->curr_time;
	else
		return tdt::real{};
}

void NotificationHelper::advance_curr_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<NotificationComponent>(id);
	if(comp) // Negative values intentionally allow for cooldown prolonging.
		comp->curr_time += val;
}
