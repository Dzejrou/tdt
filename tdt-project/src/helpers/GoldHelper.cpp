#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <gui/GUI.hpp>
#include <helpers/FactionHelper.hpp>
#include <tools/Player.hpp>
#include "GoldHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::GoldCache cache{Component::NO_ENTITY, nullptr};
#endif

void GoldHelper::set_curr_gold(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	GoldComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GoldComponent);
	if(comp)
	{
		// Stats used for transaction registering.
		bool positive = comp->curr_amount >= val;
		auto diff = positive ? comp->curr_amount - val : val - comp->curr_amount - val;
		register_transaction_(ents, *comp, id, diff, positive);
		
		comp->curr_amount = val;
	}
}

tdt::uint GoldHelper::get_curr_gold(EntitySystem& ents, tdt::uint id)
{
	GoldComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GoldComponent);
	if(comp)
		return comp->curr_amount;
	else
		return tdt::uint{};
}

void GoldHelper::set_max_gold(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	GoldComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GoldComponent);
	if(comp)
	{
		comp->max_amount = val;
		register_transaction_(ents, *comp, id, 0); // No change to player's gold.
	}
}

tdt::uint GoldHelper::get_max_gold(EntitySystem& ents, tdt::uint id)
{
	GoldComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GoldComponent);
	if(comp)
		return comp->max_amount;
	else
		return tdt::uint{};
}

tdt::uint GoldHelper::add_gold(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	GoldComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GoldComponent);
	if(comp)
	{
		tdt::uint rem{};
		if(comp->curr_amount + val <= comp->max_amount)
			comp->curr_amount += val;
		else
		{
			rem = comp->curr_amount + val - comp->max_amount;
			comp->curr_amount = comp->max_amount;
		}
		register_transaction_(ents, *comp, id, val, true);
		return rem;
	}
	else
		return tdt::uint{};
}

tdt::uint GoldHelper::sub_gold(EntitySystem& ents, tdt::uint id, tdt::uint val, bool reg)
{
	GoldComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GoldComponent);
	if(comp)
	{
		bool has_enough = comp->curr_amount >= val;
		auto diff = has_enough ? val : comp->curr_amount;
		auto remainder = val - diff; // Gold that could not be subtracted.
		if(reg)
			register_transaction_(ents, *comp, id, diff, false);

		comp->curr_amount -= diff;
		return remainder;
	}
	else
		return tdt::uint{};
}

tdt::uint GoldHelper::transfer_all_gold(EntitySystem& ents, tdt::uint id_from, tdt::uint id_to)
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
		register_transaction_(ents, *comp_to, id_to, diff, true);
		register_transaction_(ents, *comp_from, id_from, diff, false);

		return diff;
	}
	else
		return tdt::uint{};

}

bool GoldHelper::gold_full(EntitySystem& ents, tdt::uint id)
{
	GoldComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, GoldComponent);
	if(comp)
		return comp->curr_amount >= comp->max_amount;
	else
		return false;
}

void GoldHelper::register_transaction_(EntitySystem& ents, GoldComponent& comp, tdt::uint id, tdt::uint val, bool add)
{
	// Updates info if the entity is being currently tracked.
	auto& tracker = GUI::instance().get_tracker();
	if(tracker.get_tracked_entity() == id)
		tracker.update_tracking("GOLD_VALUE", std::to_string(comp.curr_amount)
								+ " / "	+ std::to_string(comp.max_amount));

	// If it was a gold vault, update the player's gold.
	auto& comp_list = ents.get_component_list();
	auto ent = comp_list.find(id);
	if(ent != comp_list.end() && ent->second.test(StructureComponent::type)
	   && FactionHelper::get_faction(ents, id) == FACTION::FRIENDLY) // It has a gold component if this was called.
	{
		if(add)
			Player::instance().add_gold(val);
		else
			Player::instance().sub_gold(val);
	}
}
