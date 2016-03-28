#include "FactionHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void FactionHelper::set_faction(EntitySystem& ents, tdt::uint id, FACTION val)
{
	auto comp = ents.get_component<FactionComponent>(id);
	if(comp)
		comp->faction = val;
}

FACTION FactionHelper::get_faction(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<FactionComponent>(id);
	if(comp)
		return comp->faction;
	else
		return FACTION::NEUTRAL;
}

const std::string& FactionHelper::get_faction_name(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<FactionComponent>(id);
	if(comp)
		return ents.FACTION_NAME[(int)comp->faction];
	else
		return ents.FACTION_NAME[2]; // Neutral is the default.
}
