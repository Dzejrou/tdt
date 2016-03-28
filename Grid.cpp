#include "Grid.hpp"
#include "Helpers.hpp"
#include "EntitySystem.hpp"
#include "Util.hpp"
#include "Enums.hpp"
#include "Components.hpp"
#include <algorithm>

bool Grid::in_board(tdt::uint id) const
{
	return std::find(nodes_.begin(), nodes_.end(), id) != nodes_.end();
}

const std::set<tdt::uint>& Grid::get_freed() const
{
	return freed_;
}

const std::set<tdt::uint>& Grid::get_unfreed() const
{
	return unfreed_;
}

void Grid::clear_freed()
{
	freed_.clear();
}

void Grid::clear_unfreed()
{
	unfreed_.clear();
}

tdt::uint Grid::add_node(EntitySystem& ents, Ogre::Vector2 pos)
{
	if(nodes_.size() < width_ * height_)
	{
		auto id = ents.create_entity();
		ents.add_component<GridNodeComponent>(id);
		ents.add_component<PhysicsComponent>(id);
		PhysicsHelper::set_2d_position(ents, id, pos);
		nodes_.push_back(id);

		return id;
	}
	else
		return Component::NO_ENTITY;
}

void Grid::add_freed(tdt::uint id)
{
	if(in_board(id))
	{
		freed_.insert(id);

		bool already_free{false};
		for(const auto& node : free_nodes_)
		{
			if(node == id)
			{
				already_free = true;
				break;
			}
		}
		if(!already_free)
			free_nodes_.emplace_back(id);
	}
}

void Grid::add_unfreed(tdt::uint id)
{
	if(in_board(id))
	{
		unfreed_.insert(id);
		free_nodes_.erase(std::remove(free_nodes_.begin(), free_nodes_.end(), id),
						  free_nodes_.end());
	}
}

void Grid::remove_node(tdt::uint id)
{
	std::remove(nodes_.begin(), nodes_.end(), id);
	std::remove(free_nodes_.begin(), free_nodes_.end(), id);
}

tdt::uint Grid::get_node(tdt::uint x, tdt::uint y) const
{
	if(x < width_ && y < height_ && (x + y * width_) < nodes_.size())
		return nodes_[x + y * width_];
	else
		return Component::NO_ENTITY;
}

tdt::uint Grid::get_node_from_position(tdt::real x, tdt::real y) const
{
	x = (x - start_.x) / distance_;
	y = (y - start_.y) / distance_;
	tdt::uint res_x = (tdt::uint)x;
	tdt::uint res_y = (tdt::uint)y;
	tdt::real off_x = x - res_x;
	tdt::real off_y = y - res_y;

	// Finds the closest.
	if(off_x > distance_ / 200)
		++res_x;
	if(off_y > distance_ / 200)
		++res_y;

	return get_node(res_x, res_y);
}

void Grid::create_graph(EntitySystem& ents, Ogre::Vector2 start, tdt::uint w, tdt::uint h, tdt::real d)
{
	for(const auto& node : nodes_)
		DestructorHelper::destroy(ents, node, true);
	nodes_.clear();
	nodes_.reserve(w * h);
	ents.cleanup(); // Create special cleanup only for entities with a given component?

	start_ = start;
	width_ = w;
	height_ = h;
	distance_ = d;
	starting_index_ = Component::NO_ENTITY;

	std::vector<GridNodeComponent*> comps(width_ * height_); // Keep pointers to components for fast access.

	Ogre::Vector2 pos{start_};
	auto node_count = w * h;
	for(tdt::uint i = 0; i < node_count; ++i)
	{
		pos.x = (i % width_) * distance_;
		pos.y = (i / width_) * distance_;
		auto id = add_node(ents, pos);
		auto comp = ents.get_component<GridNodeComponent>(id);
		if(comp) // Should never be false though as the component is added 2 lines above...
		{
			comps[i] = comp;
			comps[i]->x = i % width_;
			comps[i]->y = i / width_;
		}
	}

	// Link nodes.
	for(tdt::uint i = 0; i < node_count; ++i)
		link_(i, comps);

	free_nodes_ = nodes_;
}

tdt::real Grid::get_distance() const
{
	return distance_;
}

Grid& Grid::instance()
{
	static Grid inst{};

	return inst;
}

tdt::uint Grid::get_random_free_node() const
{
	if(free_nodes_.size() > 0)
		return free_nodes_[util::get_random(0, free_nodes_.size() - 1)];
	else
		return Component::NO_ENTITY;
}

Ogre::Vector2 Grid::get_center_position(EntitySystem& ents) const
{
	auto center_node = get_node(width_ / 2, height_ / 2);
	return PhysicsHelper::get_2d_position(ents, center_node);
}

bool Grid::place_at_random_free_node(EntitySystem& ents, tdt::uint id)
{
	auto node = get_random_free_node();
	if(node != Component::NO_ENTITY)
		PhysicsHelper::set_2d_position(ents, id, PhysicsHelper::get_2d_position(ents, node));

	return node != Component::NO_ENTITY;
}

bool Grid::distribute_to_adjacent_free_nodes(EntitySystem& ents, tdt::uint node, const std::vector<tdt::uint>& ids)
{
	if(!GridNodeHelper::is_free(ents, node))
		return false;

	std::deque<tdt::uint> queue{};
	std::set<tdt::uint> visited{};
	tdt::uint distribution_count{};

	queue.push_back(node);
	while(!queue.empty() && distribution_count < ids.size())
	{
		auto current = queue.front();
		queue.pop_front();
		if(!visited.insert(current).second)
			continue; // Already visited.

		// It's free because of check on neighbours and node at the top.
		PhysicsHelper::set_2d_position(ents, ids[distribution_count++],
									   PhysicsHelper::get_2d_position(ents, current));
	
		const auto& neighbours = GridNodeHelper::get_neighbours(ents, current);
		for(const auto& neighbour : neighbours)
		{
			if(visited.count(neighbour) == 0 && GridNodeHelper::is_free(ents, neighbour))
				queue.push_back(neighbour);
		}
	}

	return distribution_count == ids.size();
}

void Grid::link_(tdt::uint index, std::vector<GridNodeComponent*>& comps)
{
	if(!in_board(index) || !comps[index])
		return;
	tdt::uint x{comps[index]->x}, y{comps[index]->y};
	bool bottom{y == height_ - 1}, top{y == 0}, left{x == 0}, right = {x == width_ - 1};

	if(!right && comps[index + 1])
		comps[index]->neighbours[DIRECTION::RIGHT] = index + 1;

	if(!left && comps[index - 1])
		comps[index]->neighbours[DIRECTION::LEFT] = index - 1;

	if(!bottom && comps[index + width_])
		comps[index]->neighbours[DIRECTION::DOWN] = index + width_;

	if(!top && comps[index - width_])
		comps[index]->neighbours[DIRECTION::UP] = index - width_;

	if(!bottom && !left && comps[index + width_ - 1])
		comps[index]->neighbours[DIRECTION::DOWN_LEFT] = index + width_ - 1;

	if(!top && !left && comps[index - width_ - 1])
		comps[index]->neighbours[DIRECTION::UP_LEFT] = index - width_ - 1;

	if(!bottom && !right && comps[index + width_ + 1])
		comps[index]->neighbours[DIRECTION::DOWN_RIGHT] = index + width_ + 1;

	if(!top && !right && comps[index - width_ + 1])
		comps[index]->neighbours[DIRECTION::UP_RIGHT] = index - width_ + 1;
}
