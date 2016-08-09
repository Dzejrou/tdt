#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "NameHelper.hpp"

static tdt::cache::NameCache cache{Component::NO_ENTITY, nullptr};

void NameHelper::set_name(EntitySystem& ents, tdt::uint id, const std::string& val)
{ // Note: No need to update the entity viewer as this is only used during load or testing.
	NameComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, NameComponent);
	if(comp)
		comp->name = val;
}

const std::string& NameHelper::get_name(EntitySystem& ents, tdt::uint id)
{
	NameComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, NameComponent);
	if(comp)
		return comp->name;
	else
		return ents.NO_BLUEPRINT;
}
