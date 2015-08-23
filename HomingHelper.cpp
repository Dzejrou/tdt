#include "HomingHelper.hpp"

void HomingHelper::set_source(EntitySystem& ents, std::size_t id, std::size_t source)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		comp->source = source;
}

std::size_t HomingHelper::get_source(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		return comp->source;
	else
		return Component::NO_ENTITY;
}

void HomingHelper::set_target(EntitySystem& ents, std::size_t id, std::size_t target)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		comp->target = target;
}

std::size_t HomingHelper::get_target(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		return comp->target;
	else
		return Component::NO_ENTITY;
}

void HomingHelper::set_dmg(EntitySystem& ents, std::size_t id, std::size_t dmg)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		comp->dmg = dmg;
}

std::size_t HomingHelper::get_dmg(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<HomingComponent>(id);
	if(comp)
		return comp->dmg;
	else
		return std::size_t{};
}
