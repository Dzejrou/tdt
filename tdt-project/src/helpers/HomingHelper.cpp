#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "HomingHelper.hpp"

static tdt::cache::HomingCache cache{Component::NO_ENTITY, nullptr};

void HomingHelper::set_source(EntitySystem& ents, tdt::uint id, tdt::uint source)
{
	HomingComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HomingComponent);
	if(comp)
		comp->source = source;
}

tdt::uint HomingHelper::get_source(EntitySystem& ents, tdt::uint id)
{
	HomingComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HomingComponent);
	if(comp)
		return comp->source;
	else
		return Component::NO_ENTITY;
}

void HomingHelper::set_target(EntitySystem& ents, tdt::uint id, tdt::uint target)
{
	HomingComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HomingComponent);
	if(comp)
		comp->target = target;
}

tdt::uint HomingHelper::get_target(EntitySystem& ents, tdt::uint id)
{
	HomingComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HomingComponent);
	if(comp)
		return comp->target;
	else
		return Component::NO_ENTITY;
}

void HomingHelper::set_dmg(EntitySystem& ents, tdt::uint id, tdt::uint dmg)
{
	HomingComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HomingComponent);
	if(comp)
		comp->dmg = dmg;
}

tdt::uint HomingHelper::get_dmg(EntitySystem& ents, tdt::uint id)
{
	HomingComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, HomingComponent);
	if(comp)
		return comp->dmg;
	else
		return tdt::uint{};
}
