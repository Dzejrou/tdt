#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "LimitedLifeSpanHelper.hpp"

static tdt::cache::LimitedLifeSpanCache cache{Component::NO_ENTITY, nullptr};

void LimitedLifeSpanHelper::set_max_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	LimitedLifeSpanComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, LimitedLifeSpanComponent);
	if(comp)
		comp->max_time = val;
}

tdt::real LimitedLifeSpanHelper::get_max_time(EntitySystem& ents, tdt::uint id)
{
	LimitedLifeSpanComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, LimitedLifeSpanComponent);
	if(comp)
		return comp->max_time;
	else
		return tdt::real{};
}

tdt::real LimitedLifeSpanHelper::get_curr_time(EntitySystem& ents, tdt::uint id)
{
	LimitedLifeSpanComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, LimitedLifeSpanComponent);
	if(comp)
		return comp->curr_time;
	else
		return tdt::real{};
}

void LimitedLifeSpanHelper::advance_curr_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	LimitedLifeSpanComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, LimitedLifeSpanComponent);
	if(comp)
		comp->curr_time += val;
}
