#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "CounterHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::CounterCache cache{Component::NO_ENTITY, nullptr};
#endif

bool CounterHelper::increment(EntitySystem& ents, tdt::uint id)
{
	CounterComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CounterComponent);
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
	CounterComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CounterComponent);
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
	CounterComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CounterComponent);
	if(comp)
		comp->curr_value = val;
}

tdt::uint CounterHelper::get_curr_value(EntitySystem& ents, tdt::uint id)
{
	CounterComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CounterComponent);
	if(comp)
		return comp->curr_value;
	else
		return tdt::uint{};
}

void CounterHelper::set_max_value(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	CounterComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CounterComponent);
	if(comp)
		comp->max_value = val;
}

tdt::uint CounterHelper::get_max_value(EntitySystem& ents, tdt::uint id)
{
	CounterComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, CounterComponent);
	if(comp)
		return comp->max_value;
	else
		return tdt::uint{};
}
