#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "ExplosionHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::ExplosionCache cache{Component::NO_ENTITY, nullptr};
#endif

void ExplosionHelper::set_delta(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	ExplosionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ExplosionComponent);
	if(comp)
		comp->delta = val;
}

tdt::real ExplosionHelper::get_delta(EntitySystem& ents, tdt::uint id)
{
	ExplosionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ExplosionComponent);
	if(comp)
		return comp->delta;
	else
		return tdt::real{};
}

void ExplosionHelper::set_max_radius(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	ExplosionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ExplosionComponent);
	if(comp)
		comp->max_radius = val;
}

tdt::real ExplosionHelper::get_max_radius(EntitySystem& ents, tdt::uint id)
{
	ExplosionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ExplosionComponent);
	if(comp)
		return comp->max_radius;
	else
		return tdt::real{};
}

tdt::real ExplosionHelper::get_curr_radius(EntitySystem& ents, tdt::uint id)
{
	ExplosionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ExplosionComponent);
	if(comp)
		return comp->curr_radius;
	else
		return tdt::real{};
}

void ExplosionHelper::increase_curr_radius(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	ExplosionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ExplosionComponent);
	if(comp)
		comp->curr_radius += val;
}
