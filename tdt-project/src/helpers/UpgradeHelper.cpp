#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include <lppscript/LppScript.hpp>
#include<gui/GUI.hpp>
#include "UpgradeHelper.hpp"

void UpgradeHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string& UpgradeHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

tdt::uint UpgradeHelper::set_experience(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
	{
		tdt::uint remainder{};
		if(val <= comp->exp_needed)
			comp->experience = val;
		else
		{
			remainder = val - comp->exp_needed;
			comp->experience = comp->exp_needed;
		}
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
		{
			tracker.update_tracking("EXP_VALUE", std::to_string(comp->experience)
									+ " / " + std::to_string(comp->exp_needed));
			if(comp->experience >= comp->exp_needed)
				tracker.show_upgrade_butt(true);
		}
		return remainder;
	}
	else
		return val;
}

tdt::uint UpgradeHelper::get_experience(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->experience;
	else
		return tdt::uint{};
}

tdt::uint UpgradeHelper::add_experience(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
	{
		tdt::uint remainder{};
		if(comp->experience + val <= comp->exp_needed)
			comp->experience += val;
		else
		{
			remainder = comp->experience + val - comp->exp_needed;
			comp->experience = comp->exp_needed;
		}
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
		{
			tracker.update_tracking("EXP_VALUE", std::to_string(comp->experience)
									+ " / " + std::to_string(comp->exp_needed));
			if(comp->experience >= comp->exp_needed)
				tracker.show_upgrade_butt(true);
		}
		return remainder;
	}
	else
		return val;
}

void UpgradeHelper::set_exp_needed(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
	{
		comp->exp_needed = val;
		if(comp->experience > val)
			comp->experience = val;

		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
		{
			tracker.update_tracking("EXP_VALUE", std::to_string(comp->experience)
									+ " / " + std::to_string(comp->exp_needed));
			if(comp->experience >= comp->exp_needed)
				tracker.show_upgrade_butt(true);
		}
	}
}

tdt::uint UpgradeHelper::get_exp_needed(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->exp_needed;
	else
		return tdt::uint{};
}

void UpgradeHelper::set_level(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
	{
		comp->level = (val > comp->level_cap ? comp->level_cap : val);
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("LVL_VALUE", std::to_string(comp->level)
									+ " / " + std::to_string(comp->level_cap));
	}
}

tdt::uint UpgradeHelper::get_level(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->level;
	else
		return tdt::uint{};
}

void UpgradeHelper::set_level_cap(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
	{
		comp->level_cap = val;
		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("LVL_VALUE", std::to_string(comp->level)
									+ " / " + std::to_string(comp->level_cap));
	}
}

tdt::uint UpgradeHelper::get_level_cap(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->level_cap;
	else
		return tdt::uint{};
}

bool UpgradeHelper::can_level_up(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->experience >= comp->exp_needed && comp->level < comp->level_cap;
	else
		return false;
}

void UpgradeHelper::upgrade(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp && comp->level < comp->level_cap && comp->experience >= comp->exp_needed)
	{
		comp->experience = 0;
		++comp->level;
		lpp::Script::instance().call<void, tdt::uint>(comp->blueprint + ".upgrade", id);

		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("EXP_VALUE", std::to_string(comp->experience)
									+ " / " + std::to_string(comp->exp_needed));
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("LVL_VALUE", std::to_string(comp->level)
									+ " / " + std::to_string(comp->level_cap));
	}
}
