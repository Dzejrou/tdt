#include "Grid.hpp"

bool Grid::in_board(std::size_t id) const
{
	return std::find(nodes_.begin(), nodes_.end(), id) != nodes_.end();
}

const std::set<std::size_t>& Grid::get_freed() const
{
	return freed_;
}

const std::set<std::size_t>& Grid::get_unfreed() const
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

std::size_t Grid::add_node(EntitySystem& ents, Ogre::Vector2 pos)
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

void Grid::add_freed(std::size_t id)
{
	if(in_board(id))
		freed_.insert(id);
}

void Grid::add_unfreed(std::size_t id)
{
	if(in_board(id))
		unfreed_.insert(id);
}

void Grid::remove_node(std::size_t id)
{
	std::remove(nodes_.begin(), nodes_.end(), id);
}

std::size_t Grid::get_node(std::size_t x, std::size_t y) const
{
	if(in_board(x + y * width_))
		return nodes_[x + y * width_];
	else
		return Component::NO_ENTITY;
}

std::size_t Grid::get_node_from_position(Ogre::Real x, Ogre::Real y) const
{
	x = (x - start_.x) / distance_;
	y = (y - start_.y) / distance_;
	std::size_t res_x = (std::size_t)x;
	std::size_t res_y = (std::size_t)y;
	Ogre::Real off_x = x - res_x;
	Ogre::Real off_y = y - res_y;

	// Finds the closest.
	if(off_x > distance_ / 200)
		++res_x;
	if(off_y > distance_ / 200)
		++res_y;

	return get_node(res_x, res_y);
}

void Grid::create_graph(EntitySystem& ents, Ogre::Vector2 start, std::size_t w, std::size_t h, Ogre::Real d)
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
	for(std::size_t i = 0; i < node_count; ++i)
	{
		pos.x = (i % width_) * distance_;
		pos.y = (i / height_) * distance_;
		auto id = add_node(ents, pos);
		auto comp = ents.get_component<GridNodeComponent>(id);
		if(comp) // Should never be false though as the component is added 2 lines above...
			comps[i] = comp;
		comps[i]->x = i % width_;
		comps[i]->y = i / height_;
	}

	// Link nodes.
	for(std::size_t i = 0; i < node_count; ++i)
		link_(i, comps);
}

Ogre::Real Grid::get_distance() const
{
	return distance_;
}

Grid& Grid::instance()
{
	static Grid inst{};

	return inst;
}

void Grid::link_(std::size_t index, std::vector<GridNodeComponent*>& comps)
{
	if(!in_board(index) || !comps[index])
		return;
	std::size_t x{comps[index]->x}, y{comps[index]->y};
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
