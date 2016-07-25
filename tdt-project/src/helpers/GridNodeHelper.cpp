#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include <tools/Grid.hpp>
#include <tools/SelectionBox.hpp>
#include <tools/Util.hpp>
#include "GridNodeHelper.hpp"

const std::array<tdt::uint, GridNodeComponent::neighbour_count>& GridNodeHelper::get_neighbours(EntitySystem& ents, tdt::uint id)
{
	static std::array<tdt::uint, GridNodeComponent::neighbour_count> NO_NEIGHBOURS{};
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
		return comp->neighbours;
	else
		return NO_NEIGHBOURS;
}

bool GridNodeHelper::is_free(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
		return comp->free;
	else
		return true;
}

bool GridNodeHelper::area_free(EntitySystem& ents, tdt::uint center, tdt::uint radius)
{
	tdt::uint x, y;
	std::tie(x, y) = get_board_coords(ents, center);
	x = x - radius;
	y = y - radius;
	radius = radius * 2 + 1;
	for(tdt::uint i = 0; i < radius; ++i)
	{
		for(tdt::uint j = 0; j < radius; ++j)
		{
			auto id = Grid::instance().get_node(x + i, y + j);
			if(!is_free(ents, id) || get_resident(ents, id) != Component::NO_ENTITY)
				return false;
		}
	}
	return true;
}

void GridNodeHelper::set_free(EntitySystem& ents, tdt::uint id, bool val)
{
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
	{
			comp->free = val;
			if(val)
			{
				Grid::instance().add_freed(id);
				comp->resident = Component::NO_ENTITY;
			}
			else
				Grid::instance().add_unfreed(id);
	}
}

void GridNodeHelper::set_free_selected(EntitySystem& ents, SelectionBox& box, bool val)
{
	for(auto& id : box.get_selected_entities())
		set_free(ents, id, val);
}

std::tuple<tdt::uint, tdt::uint> GridNodeHelper::get_board_coords(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
		return std::make_tuple(comp->x, comp->y);
	else 
		return std::make_tuple(Component::NO_ENTITY, Component::NO_ENTITY);
}

void GridNodeHelper::set_resident(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
	{
		if(comp->resident == Component::NO_ENTITY)
		{
			comp->resident = val;
			comp->free = false;
		}
	}
}

tdt::uint GridNodeHelper::get_resident(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
		return comp->resident;
	else
		return Component::NO_ENTITY;
}

tdt::uint GridNodeHelper::get_manhattan_distance(EntitySystem& ents, tdt::uint id1, tdt::uint id2)
{
	tdt::uint x1, y1;
	std::tie(x1, y1) = get_board_coords(ents, id1);

	tdt::uint x2, y2;
	std::tie(x2, y2) = get_board_coords(ents, id2);

	return util::abs(int(x1 - x2)) + util::abs(int(y1 - y2));
}

tdt::uint GridNodeHelper::get_node_in_dir(EntitySystem& ents, tdt::uint id, int dir)
{
	auto pos = PhysicsHelper::get_position(ents, id);
	tdt::uint node = Grid::instance().get_node_from_position(pos.x, pos.z);

	if(dir == DIRECTION::NONE)
		return node;
	
	auto comp = ents.get_component<GridNodeComponent>(node);
	if(comp)
		return comp->neighbours[dir];
	else
		return Component::NO_ENTITY;
}

void GridNodeHelper::set_portal_neighbour(EntitySystem& ents, tdt::uint id, tdt::uint portal)
{
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
		comp->neighbours[DIRECTION::PORTAL] = portal;
}
