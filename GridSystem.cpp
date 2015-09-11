#include "GridSystem.hpp"

GridSystem::GridSystem(EntitySystem& ents, Ogre::SceneManager& scene)
	: entities_{ents}, scene_mgr_{scene}, width_{0}, height_{0},
	  start_{0, 0}, distance_{0}, board_{},
	  graphics_loaded_{false}, graph_visible_{false},
	  freed_{}, unfreed_{}
{ /* DUMMY BODY */ }

void GridSystem::update(Ogre::Real)
{
	// Correct pathfinding.
	if(!unfreed_.empty())
	{
		for(auto& ent : entities_.get_component_container<PathfindingComponent>())
		{
			for(auto node : unfreed_)
			{
				if(std::find(ent.second.path_queue.begin(), ent.second.path_queue.end(),
							 node) != ent.second.path_queue.end())
				{
					if(!perform_a_star(ent.first, ent.second.target_id))
					{ // Can't correct the path.
						ent.second.path_queue.clear();
						ent.second.target_id = Component::NO_ENTITY;
					}
					break; // Other unfreed nodes were taken into account already.
				}
			}
		}
	}
	unfreed_.clear();
}

std::size_t GridSystem::add_node(Ogre::Real x, Ogre::Real y, Ogre::Real z)
{
	auto id = entities_.create_entity();
	entities_.add_component<GridNodeComponent>(id);
	auto& phys_comp = entities_.add_component<PhysicsComponent>(id);
	phys_comp.position = Ogre::Vector3{x, y + 10, z};

	return id;
}

void GridSystem::create_graph(std::size_t width, std::size_t height, Ogre::Real dist,
							  Ogre::Real start_x, Ogre::Real start_y)
{
	width_ = width;
	height_ = height;
	distance_ = dist;
	start_.x = start_x;
	start_.y = start_y;

	board_.clear();
	board_.resize(width_ * height_);
	std::vector<GridNodeComponent*> comps(width_ * height_); // Keep pointers to components for fast access.

	Ogre::Real x{start_.x};
	Ogre::Real y{start_.y};
	for(std::size_t i = 0; i < board_.size(); ++i)
	{
		x = (i % width_) * distance_;
		y = (i / height_) * distance_;
		board_[i] = add_node(x, 0, y);
		auto comp = entities_.get_component<GridNodeComponent>(board_[i]);
		if(comp) // Should never be false though as the component is added 2 lines above...
			comps[i] = comp;
		comps[i]->x = i % width_;
		comps[i]->y = i / height_;
	}

	// Link nodes.
	for(std::size_t i = 0; i < board_.size(); ++i)
		link_(i, comps);

	create_graphics();
}

std::size_t GridSystem::get_node(std::size_t w, std::size_t h) const
{
	if(in_board_(w + h * width_))
		return board_[w + h * width_];
	else
		return Component::NO_ENTITY;
}

std::size_t GridSystem::get_node_from_position(Ogre::Real x, Ogre::Real y) const
{ // Note: Because of this method the board should start in positive coordinates.
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

void GridSystem::create_graphics()
{
	for(auto& ent : entities_.get_component_container<GridNodeComponent>())
	{
		auto& graph_comp = entities_.add_component<GraphicsComponent>(ent.first);

		graph_comp.mesh = "cube.mesh";
		graph_comp.material = "colour/blue";
		GraphicsHelper::init_graphics_component(entities_, entities_.get_scene_manager(), ent.first);
		graph_comp.entity->setQueryFlags((Ogre::uint32)ENTITY_TYPE::NONE);

		graph_comp.entity->setMaterialName(graph_comp.material);
		graph_comp.node->setScale(5, 10, 5);
		graph_comp.node->setVisible(false);

		auto phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
		if(phys_comp)
			graph_comp.node->setPosition(phys_comp->position);
	}
	graphics_loaded_ = true;
}

void GridSystem::delete_graphics()
{
	for(auto& ent : entities_.get_component_container<GridNodeComponent>())
		entities_.delete_component<GraphicsComponent>(ent.first);
	graphics_loaded_ = false;
	graph_visible_ = false;
}

void GridSystem::set_visible(bool on_off)
{
	if(!graphics_loaded_ || on_off == graph_visible_)
		return;
	
	graph_visible_ = on_off;

	// Nodes.
	for(auto& ent : entities_.get_component_container<GridNodeComponent>())
	{
		auto graph_comp = entities_.get_component<GraphicsComponent>(ent.first);
		if(graph_comp)
			graph_comp->node->setVisible(on_off);
	}
}

bool GridSystem::is_visible() const
{
	if(!graphics_loaded_)
		return false;
	else
		return graph_visible_;
}

std::array<std::size_t, 8> GridSystem::get_neighbours(std::size_t id) const
{
	auto comp = entities_.get_component<GridNodeComponent>(id);
	if(comp)
		return comp->neighbours;
	else
		return std::array<std::size_t, GridNodeComponent::neighbour_count>();
}

bool GridSystem::is_free(std::size_t id) const
{
	auto comp = entities_.get_component<GridNodeComponent>(id);
	if(comp)
		return comp->free;
	else
		return false;
}

bool GridSystem::area_free(std::size_t center, std::size_t radius) const
{
	std::size_t x, y;
	std::tie(x, y) = get_board_coords(center);
	x = x - radius;
	y = y - radius;
	radius = radius * 2 + 1;
	for(std::size_t i = 0; i < radius; ++i)
	{
		for(std::size_t j = 0; j < radius; ++j)
		{
			if(!is_free(get_node(x + i, y + j)) ||
			   !entities_.has_component<GridNodeComponent>(get_node(x + i, y + j)))
				return false;
		}
	}
	return true;
}

void GridSystem::set_free(std::size_t id, bool on_off)
{
	auto comp = entities_.get_component<GridNodeComponent>(id);
	if(comp)
	{
			comp->free = on_off;
			if(on_off)
				comp->resident = Component::NO_ENTITY;
			if(graphics_loaded_)
			{
				auto graph_comp = entities_.get_component<GraphicsComponent>(id);

				if(graph_comp)
				{
					graph_comp->entity->setMaterialName(
						on_off ? "colour/blue" : "colour/red"
					);
				}
			}
			if(on_off)
				freed_.emplace_back(id);
			else
				unfreed_.emplace_back(id);
	}
}

void GridSystem::set_free_selected(SelectionBox& box, bool on_off)
{
	for(auto& ent : box.get_selected_entities())
		set_free(ent, on_off);
}

std::size_t GridSystem::get_manhattan_distance(std::size_t id1, std::size_t id2) const
{
	std::size_t x1, y1;
	std::tie(x1, y1) = get_board_coords(id1);

	std::size_t x2, y2;
	std::tie(x2, y2) = get_board_coords(id2);

	return util::abs(int(x1 - x2)) + util::abs(int(y1 - y2));
}

std::tuple<std::size_t, std::size_t> GridSystem::get_board_coords(std::size_t id) const
{
	auto comp = entities_.get_component<GridNodeComponent>(id);
	if(comp)
		return std::make_tuple(comp->x, comp->y);
	else // Should not happen as this will be accessed only from within the GridSystem.
		return std::tuple<std::size_t, std::size_t>{};
}

void GridSystem::place_structure(std::size_t ent_id, std::size_t node_id, std::size_t radius)
{
	// TODO: Possibly return if the entity has a movement component?
	auto struct_comp = entities_.get_component<StructureComponent>(ent_id);
	if(!struct_comp || (struct_comp && struct_comp->walk_through))
		return;

	std::size_t x, y;
	std::tie(x, y) = get_board_coords(node_id);
	std::size_t start_node = get_node(x - radius, y - radius);
	std::tie(x, y) = get_board_coords(start_node);
	std::size_t target_node{};

	// This will check if the entire area is free first.
	if(!area_free(node_id, radius))
		return;

	radius = radius * 2 + 1;
	for(std::size_t i = 0; i < radius; ++i)
	{
		for(std::size_t j = 0; j < radius; ++j)
		{
			target_node = get_node(x + i, y + j);
			if(!struct_comp->walk_through)
				set_free(target_node, false);
			set_resident(target_node, ent_id);
			struct_comp->residences.push_back(target_node);
		}
	}
}

void GridSystem::set_resident(std::size_t node_id, std::size_t res_id)
{
	auto comp = entities_.get_component<GridNodeComponent>(node_id);
	if(comp)
	{
		if(comp->resident == Component::NO_ENTITY)
		{
			comp->resident = res_id;
			comp->free = false;
		}
	}
}

std::size_t GridSystem::get_resident(std::size_t node_id) const
{
	auto comp = entities_.get_component<GridNodeComponent>(node_id);
	if(comp)
		return comp->resident;
	else
		return Component::NO_ENTITY;
}

std::size_t GridSystem::get_node_in_dir(std::size_t id, int dir) const
{
	auto pos = PhysicsHelper::get_position(entities_, id);
	std::size_t node = get_node_from_position(pos.x, pos.z);

	if(dir == DIRECTION::NONE)
		return node;
	
	auto comp = entities_.get_component<GridNodeComponent>(node);
	if(comp)
		return comp->neighbours[dir];
	else
		return Component::NO_ENTITY;
}

bool GridSystem::in_board_(std::size_t index) const
{
	return 0 <= index && index < board_.size();
}

void GridSystem::link_(std::size_t index, std::vector<GridNodeComponent*>& comps)
{
	if(!in_board_(index))
		return;
	std::size_t x{comps[index]->x}, y{comps[index]->y};
	bool bottom{y == height_ - 1}, top{y == 0}, left{x == 0}, right = {x == width_ - 1};

	if(!right)
		comps[index]->neighbours[DIRECTION::RIGHT] = index + 1;

	if(!left)
		comps[index]->neighbours[DIRECTION::LEFT] = index - 1;

	if(!bottom)
		comps[index]->neighbours[DIRECTION::DOWN] = index + width_;

	if(!top)
		comps[index]->neighbours[DIRECTION::UP] = index - width_;

	if(!bottom && !left)
		comps[index]->neighbours[DIRECTION::DOWN_LEFT] = index + width_ - 1;

	if(!top && !left)
		comps[index]->neighbours[DIRECTION::UP_LEFT] = index - width_ - 1;

	if(!bottom && !right)
		comps[index]->neighbours[DIRECTION::DOWN_RIGHT] = index + width_ + 1;

	if(!top && !right)
		comps[index]->neighbours[DIRECTION::UP_RIGHT] = index - width_ + 1;
