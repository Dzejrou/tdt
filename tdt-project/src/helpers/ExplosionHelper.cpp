#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "ExplosionHelper.hpp"

void ExplosionHelper::set_delta(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		comp->delta = val;
}

tdt::real ExplosionHelper::get_delta(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		return comp->delta;
	else
		return tdt::real{};
}

void ExplosionHelper::set_max_radius(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		comp->max_radius = val;
}

tdt::real ExplosionHelper::get_max_radius(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		return comp->max_radius;
	else
		return tdt::real{};
}

tdt::real ExplosionHelper::get_curr_radius(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		return comp->curr_radius;
	else
		return tdt::real{};
}

void ExplosionHelper::increase_curr_radius(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		comp->curr_radius += val;
}
