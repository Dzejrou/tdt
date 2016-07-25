#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "CounterHelper.hpp"

bool CounterHelper::increment(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<CounterComponent>(id);
	if(comp)
	{
		++comp->curr_value;
		return comp->curr_value >= comp->max_value;
	}
	else
		return false;
}

bool CounterHelper::decrement(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<CounterComponent>(id);
	if(comp && comp->curr_value > 0)
	{
		--comp->curr_value;
		return comp->curr_value >= comp->max_value;
	}
	else
		return false;
}

void CounterHelper::set_curr_value(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<CounterComponent>(id);
	if(comp)
		comp->curr_value = val;
}

tdt::uint CounterHelper::get_curr_value(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<CounterComponent>(id);
	if(comp)
		return comp->curr_value;
	else
		return tdt::uint{};
}

void CounterHelper::set_max_value(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<CounterComponent>(id);
	if(comp)
		comp->max_value = val;
}

tdt::uint CounterHelper::get_max_value(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<CounterComponent>(id);
	if(comp)
		return comp->max_value;
	else
		return tdt::uint{};
}
