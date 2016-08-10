#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <gui/GUI.hpp>
#include "ManaHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::ManaCache cache{Component::NO_ENTITY, nullptr};
#endif

void ManaHelper::add_mana(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	ManaComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaComponent);
	if(comp)
	{
		comp->curr_mana = (comp->max_mana > comp->curr_mana + val) ? comp->curr_mana + val : comp->max_mana;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("MANA_VALUE", std::to_string(comp->curr_mana)
									+ " / " + std::to_string(comp->max_mana));
	}
}

bool ManaHelper::sub_mana(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	ManaComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaComponent);
	if(comp && comp->curr_mana >= val)
	{
		comp->curr_mana -= val;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("MANA_VALUE", std::to_string(comp->curr_mana)
									+ " / " + std::to_string(comp->max_mana));
		return true;
	}
	else
		return false;
}

void ManaHelper::set_mana(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	ManaComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaComponent);
	if(comp)
	{
		comp->curr_mana = (val < comp->max_mana) ? val : comp->max_mana;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("MANA_VALUE", std::to_string(comp->curr_mana)
									+ " / " + std::to_string(comp->max_mana));
	}
}

tdt::uint ManaHelper::get_mana(EntitySystem& ents, tdt::uint id)
{
	ManaComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaComponent);
	if(comp)
		return comp->curr_mana;
	else
		return tdt::uint{};
}

void ManaHelper::set_max_mana(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	ManaComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaComponent);
	if(comp)
	{
		comp->max_mana = val;
		if(comp->curr_mana > val)
			comp->curr_mana = val;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("MANA_VALUE", std::to_string(comp->curr_mana)
									+ " / " + std::to_string(comp->max_mana));
	}
}

tdt::uint ManaHelper::get_max_mana(EntitySystem& ents, tdt::uint id)
{
	ManaComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaComponent);
	if(comp)
		return comp->max_mana;
	else
		return tdt::uint{};
}

void ManaHelper::set_regen(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	ManaComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaComponent);
	if(comp)
	{
		comp->mana_regen = val;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("MANA_VALUE", std::to_string(comp->curr_mana)
									+ " / " + std::to_string(comp->max_mana));
	}
}

tdt::uint ManaHelper::get_regen(EntitySystem& ents, tdt::uint id)
{
	ManaComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ManaComponent);
	if(comp)
		return comp->mana_regen;
	else
		return tdt::uint{};
}
