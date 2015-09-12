#include "GridSystem.hpp"

GridSystem::GridSystem(EntitySystem& ents, Ogre::SceneManager& scene)
	: entities_{ents}, scene_mgr_{scene},
	  graphics_loaded_{false}, graph_visible_{false}
{ /* DUMMY BODY */ }

void GridSystem::update(Ogre::Real)
{
	const auto& unfreed = Grid::instance().get_unfreed();
	const auto& freed = Grid::instance().get_freed();
	if(graphics_loaded_)
	{
		for(const auto& node : unfreed)
			GraphicsHelper::set_material(entities_, node, "colour/red");

		for(const auto& node : freed)
			GraphicsHelper::set_material(entities_, node, "colour/blue");
	}

	// Correct pathfinding.
	if(!unfreed.empty())
	{
		for(auto& ent : entities_.get_component_container<PathfindingComponent>())
		{
			for(auto node : unfreed)
			{
				if(std::find(ent.second.path_queue.begin(), ent.second.path_queue.end(),
							 node) != ent.second.path_queue.end())
				{
					if(!util::pathfind<util::DEFAULT_PATHFINDING_ALGORITHM>(
						entities_, ent.first, ent.second.target_id, true))
					{ // Can't correct the path.
						ent.second.path_queue.clear();
						ent.second.target_id = Component::NO_ENTITY;
					}
					break; // Other unfreed nodes were taken into account already.
				}
			}
		}
	}
	Grid::instance().clear_unfreed();
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

void GridSystem::place_structure(std::size_t ent_id, std::size_t node_id, std::size_t radius)
{
	// TODO: Possibly return if the entity has a movement component?
	auto struct_comp = entities_.get_component<StructureComponent>(ent_id);
	if(!struct_comp || (struct_comp && struct_comp->walk_through))
		return;

	Grid& grid = Grid::instance();
	std::size_t x, y;
	std::tie(x, y) = GridNodeHelper::get_board_coords(entities_, node_id);
	std::size_t start_node = grid.get_node(x - radius, y - radius);
	std::tie(x, y) = GridNodeHelper::get_board_coords(entities_, start_node);
	std::size_t target_node{};

	// This will check if the entire area is free first.
	if(!GridNodeHelper::area_free(entities_, node_id, radius))
		return;

	radius = radius * 2 + 1;
	for(std::size_t i = 0; i < radius; ++i)
	{
		for(std::size_t j = 0; j < radius; ++j)
		{
			target_node = grid.get_node(x + i, y + j);
			if(!struct_comp->walk_through)
				GridNodeHelper::set_free(entities_, target_node, false);
			GridNodeHelper::set_resident(entities_, target_node, ent_id);
			struct_comp->residences.push_back(target_node);
		}
	}
}