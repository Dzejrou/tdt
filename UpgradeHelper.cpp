#include "UpgradeHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"
#include "GUI.hpp"

void UpgradeHelper::set_blueprint(EntitySystem& ents, std::size_t id, const std::string& val)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string& UpgradeHelper::get_blueprint(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

std::size_t UpgradeHelper::set_experience(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
	{
		std::size_t remainder{};
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

std::size_t UpgradeHelper::get_experience(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->experience;
	else
		return std::size_t{};
}

std::size_t UpgradeHelper::add_experience(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
	{
		std::size_t remainder{};
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

void UpgradeHelper::set_exp_needed(EntitySystem& ents, std::size_t id, std::size_t val)
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

std::size_t UpgradeHelper::get_exp_needed(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->exp_needed;
	else
		return std::size_t{};
}

void UpgradeHelper::set_level(EntitySystem& ents, std::size_t id, std::size_t val)
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

std::size_t UpgradeHelper::get_level(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->level;
	else
		return std::size_t{};
}

void UpgradeHelper::set_level_cap(EntitySystem& ents, std::size_t id, std::size_t val)
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

std::size_t UpgradeHelper::get_level_cap(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->level_cap;
	else
		return std::size_t{};
}

bool UpgradeHelper::can_level_up(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp)
		return comp->experience >= comp->exp_needed && comp->level < comp->level_cap;
	else
		return false;
}

void UpgradeHelper::upgrade(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<UpgradeComponent>(id);
	if(comp && comp->level < comp->level_cap && comp->experience >= comp->exp_needed)
	{
		comp->experience = 0;
		++comp->level;
		lpp::Script::get_singleton().call<void, std::size_t>(comp->blueprint + ".upgrade", id);

		auto& tracker = GUI::instance().get_tracker();
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("EXP_VALUE", std::to_string(comp->experience)
									+ " / " + std::to_string(comp->exp_needed));
		if(tracker.get_tracked_entity() == id)
			tracker.update_tracking("LVL_VALUE", std::to_string(comp->level)
									+ " / " + std::to_string(comp->level_cap));
	}
}
