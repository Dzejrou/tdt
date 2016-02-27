#include "StructureHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void StructureHelper::add_residences(EntitySystem& ents, std::size_t ent_id, const std::vector<std::size_t>& residences)
{
	auto comp = ents.get_component<StructureComponent>(ent_id);
	if(comp)
	{
		for(const auto& node : residences)
			comp->residences.push_back(node);
	}
}

void StructureHelper::add_residence(EntitySystem& ents, std::size_t ent_id, std::size_t node_id)
{
	auto comp = ents.get_component<StructureComponent>(ent_id);
	if(comp)
		comp->residences.push_back(node_id);
}

void StructureHelper::set_radius(EntitySystem& ents, std::size_t id, std::size_t radius)
{
	auto comp = ents.get_component<StructureComponent>(id);
	if(comp)
		comp->radius = radius;
}

std::size_t StructureHelper::get_radius(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<StructureComponent>(id);
	if(comp)
		return comp->radius;
	else
		return std::size_t{};
}

void StructureHelper::set_walk_through(EntitySystem& ents, std::size_t id, bool on_off)
{
	auto comp = ents.get_component<StructureComponent>(id);
	if(comp)
		comp->walk_through = on_off;
}

bool StructureHelper::is_walk_through(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<StructureComponent>(id);
	if(comp)
		return comp->walk_through;
	else
		return true;
}
