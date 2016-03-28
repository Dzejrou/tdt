#include "StructureHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void StructureHelper::add_residences(EntitySystem& ents, tdt::uint ent_id, const std::vector<tdt::uint>& residences)
{
	auto comp = ents.get_component<StructureComponent>(ent_id);
	if(comp)
	{
		for(const auto& node : residences)
			comp->residences.push_back(node);
	}
}

void StructureHelper::add_residence(EntitySystem& ents, tdt::uint ent_id, tdt::uint node_id)
{
	auto comp = ents.get_component<StructureComponent>(ent_id);
	if(comp)
		comp->residences.push_back(node_id);
}

void StructureHelper::set_radius(EntitySystem& ents, tdt::uint id, tdt::uint radius)
{
	auto comp = ents.get_component<StructureComponent>(id);
	if(comp)
		comp->radius = radius;
}

tdt::uint StructureHelper::get_radius(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<StructureComponent>(id);
	if(comp)
		return comp->radius;
	else
		return tdt::uint{};
}

void StructureHelper::set_walk_through(EntitySystem& ents, tdt::uint id, bool on_off)
{
	auto comp = ents.get_component<StructureComponent>(id);
	if(comp)
		comp->walk_through = on_off;
}

bool StructureHelper::is_walk_through(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<StructureComponent>(id);
	if(comp)
		return comp->walk_through;
	else
		return true;
}
