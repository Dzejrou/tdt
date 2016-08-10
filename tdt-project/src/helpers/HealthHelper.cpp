#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <gui/GUI.hpp>
#include <gui/EntityTracker.hpp>
#include "HealthHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::HealthCache cache{Component::NO_ENTITY, nullptr};
#endif

void HealthHelper::set_health(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
	{
		if(val == 0)
			comp->alive = false;
		comp->curr_hp = val;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("HP_VALUE", std::to_string(comp->curr_hp)
									+ " / " + std::to_string(comp->max_hp));
	}
}

tdt::uint HealthHelper::get_health(EntitySystem& ents, tdt::uint id)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
		return comp->curr_hp;
	else
		return 1;
}

void HealthHelper::add_health(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
	{
		comp->curr_hp = (comp->curr_hp + val >= comp->max_hp ? comp->max_hp : comp->curr_hp + val);
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("HP_VALUE", std::to_string(comp->curr_hp)
					  				+ " / " + std::to_string(comp->max_hp));
	}
}

void HealthHelper::sub_health(EntitySystem& ents, tdt::uint id, tdt::uint val, bool ignore_armor)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
	{
		if(!ignore_armor)
			val = (comp->defense < val ? val - comp->defense : 0);

		if(comp->curr_hp <= val)
		{
			comp->curr_hp = 0;
			comp->alive = false;
		}
		else
			comp->curr_hp -= val;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("HP_VALUE", std::to_string(comp->curr_hp)
									+ " / " + std::to_string(comp->max_hp));
	}
}

void HealthHelper::heal(EntitySystem& ents, tdt::uint id)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
	{
		comp->curr_hp = comp->max_hp;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("HP_VALUE", std::to_string(comp->curr_hp)
									+ " / " + std::to_string(comp->max_hp));
	}
}

void HealthHelper::buff(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
	{
		comp->max_hp += val;
		comp->curr_hp += val;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("HP_VALUE", std::to_string(comp->curr_hp)
									+ " / " + std::to_string(comp->max_hp));
	}
}

void HealthHelper::debuff(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
	{
		if(comp->curr_hp <= val)
		{
			comp->curr_hp = 1;
			comp->max_hp = 1;
		}
		else
		{
			comp->max_hp -= val;
			comp->curr_hp -= val;
		}
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("HP_VALUE", std::to_string(comp->curr_hp)
									+ " / " + std::to_string(comp->max_hp));
	}
}

void HealthHelper::set_regen(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
		comp->regen = val;
}

tdt::uint HealthHelper::get_regen(EntitySystem& ents, tdt::uint id)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
		return comp->regen;
	else
		return tdt::uint{};
}

void HealthHelper::set_alive(EntitySystem& ents, tdt::uint id, bool val)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
		comp->alive = val;
}

bool HealthHelper::is_alive(EntitySystem& ents, tdt::uint id)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
		return comp->alive;
	else
		return false;
}

void HealthHelper::set_defense(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
		comp->defense = val;
}

tdt::uint HealthHelper::get_defense(EntitySystem& ents, tdt::uint id)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
		return comp->defense;
	else
		return tdt::uint{};
}

void HealthHelper::add_defense(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
		comp->defense += val;
}

void HealthHelper::sub_defense(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
	{
		if(comp->defense < val)
			comp->defense = 0;
		else
			comp->defense -= val;
	}
}

void HealthHelper::ubercharge(EntitySystem& ents, tdt::uint id)
{
	HealthComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HealthComponent);
	if(comp)
	{
		comp->curr_hp = Component::NO_ENTITY;
		comp->max_hp = Component::NO_ENTITY;
		comp->defense = Component::NO_ENTITY;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("HP_VALUE", "UBER");
	}
}
