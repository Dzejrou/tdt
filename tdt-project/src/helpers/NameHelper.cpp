#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "NameHelper.hpp"

void NameHelper::set_name(EntitySystem& ents, tdt::uint id, const std::string& val)
{ // Note: No need to update the entity viewer as this is only used during load or testing.
	auto comp = ents.get_component<NameComponent>(id);
	if(comp)
		comp->name = val;
}

const std::string& NameHelper::get_name(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<NameComponent>(id);
	if(comp)
		return comp->name;
	else
		return ents.NO_BLUEPRINT;
}
