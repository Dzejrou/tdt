#include "HomingHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void HomingHelper::set_source(EntitySystem& ents, tdt::uint id, tdt::uint source)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		comp->source = source;
}

tdt::uint HomingHelper::get_source(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		return comp->source;
	else
		return Component::NO_ENTITY;
}

void HomingHelper::set_target(EntitySystem& ents, tdt::uint id, tdt::uint target)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		comp->target = target;
}

tdt::uint HomingHelper::get_target(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		return comp->target;
	else
		return Component::NO_ENTITY;
}

void HomingHelper::set_dmg(EntitySystem& ents, tdt::uint id, tdt::uint dmg)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		comp->dmg = dmg;
}

tdt::uint HomingHelper::get_dmg(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		return comp->dmg;
	else
		return tdt::uint{};
}
