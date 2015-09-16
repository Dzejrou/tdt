#include "FactionHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void FactionHelper::set_faction(EntitySystem& ents, std::size_t id, FACTION val)
{
	auto comp = ents.get_component<FactionComponent>(id);
	if(comp)
		comp->faction = val;
}

FACTION FactionHelper::get_faction(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<FactionComponent>(id);
	if(comp)
		return comp->faction;
	else
		return FACTION::NEUTRAL;
}