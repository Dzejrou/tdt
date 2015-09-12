#include "GridNodeHelper.hpp"
#include "EntitySystem.hpp"
#include "Grid.hpp"
#include "SelectionBox.hpp"

const std::array<std::size_t, GridNodeComponent::neighbour_count>& GridNodeHelper::get_neighbours(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
		return comp->neighbours;
	else
		return std::array<std::size_t, GridNodeComponent::neighbour_count>();
}

bool GridNodeHelper::is_free(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
		return comp->free;
	else
		return false;
}

bool GridNodeHelper::area_free(EntitySystem& ents, std::size_t center, std::size_t radius)
{
	std::size_t x, y;
	std::tie(x, y) = get_board_coords(ents, center);
	x = x - radius;
	y = y - radius;
	radius = radius * 2 + 1;
	for(std::size_t i = 0; i < radius; ++i)
	{
		for(std::size_t j = 0; j < radius; ++j)
		{
			auto id = Grid::instance().get_node(x + i, y + j);
			if(!is_free(ents, id))
				return false;
		}
	}
	return true;
}

void GridNodeHelper::set_free(EntitySystem& ents, std::size_t id, bool val)
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

std::tuple<std::size_t, std::size_t> GridNodeHelper::get_board_coords(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
		return std::make_tuple(comp->x, comp->y);
	else 
		return std::make_tuple(Component::NO_ENTITY, Component::NO_ENTITY);
}

void GridNodeHelper::set_resident(EntitySystem& ents, std::size_t id, std::size_t val)
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

std::size_t GridNodeHelper::get_resident(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GridNodeComponent>(id);
	if(comp)
		return comp->resident;
	else
		return Component::NO_ENTITY;
}

std::size_t GridNodeHelper::get_manhattan_distance(EntitySystem& ents, std::size_t id1, std::size_t id2)
{
	std::size_t x1, y1;
	std::tie(x1, y1) = get_board_coords(ents, id1);

	std::size_t x2, y2;
	std::tie(x2, y2) = get_board_coords(ents, id2);

	return util::abs(int(x1 - x2)) + util::abs(int(y1 - y2));
}

std::size_t GridNodeHelper::get_node_in_dir(EntitySystem& ents, std::size_t id, int dir)
{
	auto pos = PhysicsHelper::get_position(ents, id);
	std::size_t node = Grid::instance().get_node_from_position(pos.x, pos.z);

	if(dir == DIRECTION::NONE)
		return node;
	
	auto comp = ents.get_component<GridNodeComponent>(node);
	if(comp)
		return comp->neighbours[dir];
	else
		return Component::NO_ENTITY;
}
