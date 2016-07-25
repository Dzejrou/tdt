#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "LimitedLifeSpanHelper.hpp"

void LimitedLifeSpanHelper::set_max_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<LimitedLifeSpanComponent>(id);
	if(comp)
		comp->max_time = val;
}

tdt::real LimitedLifeSpanHelper::get_max_time(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<LimitedLifeSpanComponent>(id);
	if(comp)
		return comp->max_time;
	else
		return tdt::real{};
}

tdt::real LimitedLifeSpanHelper::get_curr_time(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<LimitedLifeSpanComponent>(id);
	if(comp)
		return comp->curr_time;
	else
		return tdt::real{};
}

void LimitedLifeSpanHelper::advance_curr_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<LimitedLifeSpanComponent>(id);
	if(comp)
		comp->curr_time += val;
}
