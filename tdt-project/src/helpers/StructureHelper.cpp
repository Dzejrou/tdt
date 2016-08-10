#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "StructureHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::StructureCache cache{Component::NO_ENTITY, nullptr};
#endif

void StructureHelper::add_residences(EntitySystem& ents, tdt::uint id, const std::vector<tdt::uint>& residences)
{
	StructureComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, StructureComponent);
	if(comp)
	{
		for(const auto& node : residences)
			comp->residences.push_back(node);
	}
}

void StructureHelper::add_residence(EntitySystem& ents, tdt::uint id, tdt::uint node_id)
{
	StructureComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, StructureComponent);
	if(comp)
		comp->residences.push_back(node_id);
}

void StructureHelper::set_radius(EntitySystem& ents, tdt::uint id, tdt::uint radius)
{
	StructureComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, StructureComponent);
	if(comp)
		comp->radius = radius;
}

tdt::uint StructureHelper::get_radius(EntitySystem& ents, tdt::uint id)
{
	StructureComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, StructureComponent);
	if(comp)
		return comp->radius;
	else
		return tdt::uint{};
}

void StructureHelper::set_walk_through(EntitySystem& ents, tdt::uint id, bool on_off)
{
	StructureComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, StructureComponent);
	if(comp)
		comp->walk_through = on_off;
}

bool StructureHelper::is_walk_through(EntitySystem& ents, tdt::uint id)
{
	StructureComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, StructureComponent);
	if(comp)
		return comp->walk_through;
	else
		return true;
}
