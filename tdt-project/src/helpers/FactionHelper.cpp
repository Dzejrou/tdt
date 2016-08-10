#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "FactionHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::FactionCache cache{Component::NO_ENTITY, nullptr};
#endif

void FactionHelper::set_faction(EntitySystem& ents, tdt::uint id, FACTION val)
{
	FactionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, FactionComponent);
	if(comp)
		comp->faction = val;
}

FACTION FactionHelper::get_faction(EntitySystem& ents, tdt::uint id)
{
	FactionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, FactionComponent);
	if(comp)
		return comp->faction;
	else
		return FACTION::NEUTRAL;
}

const std::string& FactionHelper::get_faction_name(EntitySystem& ents, tdt::uint id)
{
	FactionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, FactionComponent);
	if(comp)
		return ents.FACTION_NAME[(int)comp->faction];
	else
		return ents.FACTION_NAME[2]; // Neutral is the default.
}
