#include "GoldHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "GUI.hpp"

void GoldHelper::set_curr_gold(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<GoldComponent>(id);
	if(comp)
	{
		comp->curr_amount = val;
		if(GUI::instance().get_tracked_entity() == id)
			GUI::instance().update_tracking("GOLD_VALUE",
											std::to_string(comp->curr_amount) + " / "
											+ std::to_string(comp->max_amount));
	}
}

std::size_t GoldHelper::get_curr_gold(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GoldComponent>(id);
	if(comp)
		return comp->curr_amount;
	else
		return std::size_t{};
}

void GoldHelper::set_max_gold(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<GoldComponent>(id);
	if(comp)
	{
		comp->max_amount = val;
		if(GUI::instance().get_tracked_entity() == id)
			GUI::instance().update_tracking("GOLD_VALUE",
											std::to_string(comp->curr_amount) + " / "
											+ std::to_string(comp->max_amount));
	}
}

std::size_t GoldHelper::get_max_gold(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GoldComponent>(id);
	if(comp)
		return comp->max_amount;
	else
		return std::size_t{};
}

std::size_t GoldHelper::add_gold(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<GoldComponent>(id);
	if(comp)
	{
		std::size_t rem{};
		if(comp->curr_amount + val <= comp->max_amount)
			comp->curr_amount += val;
		else
		{
			rem = comp->curr_amount + val - comp->max_amount;
			comp->curr_amount = comp->max_amount;
		}
		if(GUI::instance().get_tracked_entity() == id)
			GUI::instance().update_tracking("GOLD_VALUE",
											std::to_string(comp->curr_amount) + " / "
											+ std::to_string(comp->max_amount));
		return rem;
	}
	else
		return std::size_t{};
}

std::size_t GoldHelper::sub_gold(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<GoldComponent>(id);
	if(comp)
	{
		if(comp->curr_amount < val)
		{
			comp->curr_amount = 0;
			return val - comp->curr_amount;
		}
		else
		{
			comp->curr_amount -= val;
			return val;
		}
		if(GUI::instance().get_tracked_entity() == id)
			GUI::instance().update_tracking("GOLD_VALUE",
											std::to_string(comp->curr_amount) + " / "
											+ std::to_string(comp->max_amount));
	}
	else
		return std::size_t{};
}

std::size_t GoldHelper::transfer_all_gold(EntitySystem& ents, std::size_t id_from, std::size_t id_to)
{
	auto comp_from = ents.get_component<GoldComponent>(id_from);
	auto comp_to = ents.get_component<GoldComponent>(id_to);
	if(comp_from && comp_to)
	{
		auto diff = comp_to->max_amount - comp_to->curr_amount;
		if(diff >= comp_from->curr_amount)
		{
			comp_to->curr_amount += comp_from->curr_amount;
			diff = comp_from->curr_amount; // For the return value ...
			comp_from->curr_amount = 0;
		}
		else
		{
			comp_from->curr_amount -= diff;
			comp_to->curr_amount += diff;
		}
		if(GUI::instance().get_tracked_entity() == id_to)
			GUI::instance().update_tracking("GOLD_VALUE",
											std::to_string(comp_to->curr_amount) + " / "
											+ std::to_string(comp_to->max_amount));
		else if(GUI::instance().get_tracked_entity() == id_from)
			GUI::instance().update_tracking("GOLD_VALUE",
											std::to_string(comp_from->curr_amount) + " / "
											+ std::to_string(comp_from->max_amount));

		return diff;
	}
	else
		return std::size_t{};

}

bool GoldHelper::gold_full(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GoldComponent>(id);
	if(comp)
		return comp->curr_amount >= comp->max_amount;
	else
		return false;
}
