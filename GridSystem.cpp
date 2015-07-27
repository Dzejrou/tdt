#include "GridSystem.hpp"

GridSystem::GridSystem(EntitySystem& ents, Ogre::SceneManager& scene)
	: entities_{ents}, scene_mgr_{scene}, width_{0}, height_{0},
	  start_{0, 0}, distance_{0}, board_{},
	  graphics_loaded_{false}, graph_visible_{false}
{ /* DUMMY BODY */ }

void GridSystem::update(Ogre::Real)
{
	// TODO:
}

bool GridSystem::is_valid(std::size_t id) const
{
	return entities_.has_component<GridNodeComponent>(id) ||
		   entities_.has_component<GridLineComponent>(id);
}

std::size_t GridSystem::add_node(Ogre::Real x, Ogre::Real y, Ogre::Real z)
{
	auto id = entities_.create_entity();
	entities_.add_component<GridNodeComponent>(id);
	auto& phys_comp = entities_.add_component<PhysicsComponent>(id);
	phys_comp.position = Ogre::Vector3{x, y + 10, z};

	return id;
}

std::size_t GridSystem::add_line(std::size_t id1, std::size_t id2)
{
	auto id = entities_.create_entity();
	auto& line_comp = entities_.add_component<GridLineComponent>(id);

	line_comp.start_id = id1;
	line_comp.end_id = id2;
	auto pos_start = entities_.get_component<PhysicsComponent>(id1).position;
	auto pos_end = entities_.get_component<PhysicsComponent>(id2).position;
	line_comp.distance = pos_start.distance(pos_end);
	line_comp.line.reset(new Line{pos_start, pos_end});

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
		comps[i] = &entities_.get_component<GridNodeComponent>(board_[i]);
	}

	// Link nodes.
	for(std::size_t i = 0; i < height_; ++i)
	{
		for(std::size_t j = 0; j < width_ - 1; ++j)
		{
			add_line(get_node(i, j), get_node(i, j + 1));
			add_line(get_node(j, i), get_node(j + 1, i));

			// Add neighbours.
			comps[i]->neighbours[0] = i + 1; // Left.
			comps[i + 1]->neighbours[1] = i; // Right.
			comps[j]->neighbours[2] = j + 1; // Bottom.
			comps[j + 1]->neighbours[3] = j; // Top.
		}
	}
}

std::size_t GridSystem::get_node(std::size_t w, std::size_t h) const
{
	return board_[w + h * width_];
}

std::size_t GridSystem::get_node_from_position(Ogre::Real x, Ogre::Real y) const
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

void GridSystem::create_graphics()
{
	for(auto& ent : entities_.get_component_container<GridNodeComponent>())
	{
		auto& phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
		auto& graph_comp = entities_.add_component<GraphicsComponent>(ent.first);

		graph_comp.mesh = "cube.mesh";
		graph_comp.material = "colour/red";
		entities_.init_graphics_component(ent.first);
		graph_comp.entity->setQueryFlags(2);

		((Ogre::Entity*)graph_comp.entity)->setMaterialName(graph_comp.material);
		graph_comp.node->setScale(5, 10, 5);
		graph_comp.node->setPosition(phys_comp.position);
		graph_comp.node->setVisible(false);
	
	}

	for(auto& ent : entities_.get_component_container<GridLineComponent>())
	{
		auto& line_comp = entities_.get_component<GridLineComponent>(ent.first);
		auto& graph_comp = entities_.add_component<GraphicsComponent>(ent.first);

		graph_comp.entity = line_comp.line.get();
		graph_comp.node = scene_mgr_.getRootSceneNode()->createChildSceneNode();
		graph_comp.node->attachObject(graph_comp.entity);
		graph_comp.material = "colour/blue";
		graph_comp.mesh = "LINE";
		graph_comp.visible = true;
		graph_comp.node->setVisible(false);
	}

	graphics_loaded_ = true;
}

void GridSystem::delete_graphics()
{
	for(auto& ent : entities_.get_component_container<GridNodeComponent>())
		entities_.delete_component<GraphicsComponent>(ent.first);
	for(auto& ent : entities_.get_component_container<GridLineComponent>())
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
		auto& graph_comp = entities_.get_component<GraphicsComponent>(ent.first);
		graph_comp.node->setVisible(on_off);
	}

	// Links.
	for(auto& ent : entities_.get_component_container<GridLineComponent>())
	{
		auto& graph_comp = entities_.get_component<GraphicsComponent>(ent.first);
		graph_comp.node->setVisible(on_off);
	}
}

bool GridSystem::is_visible() const
{
	if(!graphics_loaded_)
		return false;
	else
		return graph_visible_;
}
