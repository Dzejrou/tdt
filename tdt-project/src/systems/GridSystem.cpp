#include <Components.hpp>
#include <tools/Pathfinding.hpp>
#include <tools/PathfindingAlgorithms.hpp>
#include <tools/Grid.hpp>
#include <helpers/Helpers.hpp>
#include <gui/GUI.hpp>
#include <set>
#include <algorithm>
#include "GridSystem.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

GridSystem::GridSystem(EntitySystem& ents, Ogre::SceneManager& scene)
	: entities_{ents}, scene_mgr_{scene},
	  graphics_loaded_{false}, graph_visible_{false}
{ /* DUMMY BODY */ }

void GridSystem::update(tdt::real)
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

	std::set<tdt::uint> processed_nodes{}; // Makes sure node aren't processed multiple times.
	for(const auto& node : unfreed)
	{
		update_neighbours_(node); // Updates a block when placed, not needed when freed.
		for(const auto& neighbour : GridNodeHelper::get_neighbours(entities_, node))
		{
			if(neighbour == Component::NO_ENTITY)
				continue;
			if(!processed_nodes.insert(neighbour).second)
				continue;
			update_neighbours_(neighbour);
		}
	}
	for(const auto& node : freed)
	{
		for(const auto& neighbour : GridNodeHelper::get_neighbours(entities_, node))
		{
			if(neighbour == Component::NO_ENTITY)
				continue;
			if(!processed_nodes.insert(neighbour).second)
				continue;
			update_neighbours_(neighbour);
		}
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
						entities_, ent.first, ent.second.target_id, util::DEFAULT_HEURISTIC{entities_}, true))
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
	Grid::instance().clear_freed();
}

void GridSystem::create_graphics()
{
	for(auto& ent : entities_.get_component_container<GridNodeComponent>())
	{
		entities_.add_component<GraphicsComponent>(ent.first);
		auto graph_comp = entities_.get_component<GraphicsComponent>(ent.first);

		if(graph_comp)
		{
			graph_comp->mesh = "cube.mesh";
			graph_comp->material = "colour/blue";
			GraphicsHelper::init_graphics_component(entities_, entities_.get_scene_manager(), ent.first);
			graph_comp->entity->setQueryFlags((Ogre::uint32)ENTITY_TYPE::NONE);

			graph_comp->entity->setMaterialName(graph_comp->material);
			graph_comp->node->setScale(5, 10, 5);
			graph_comp->node->setVisible(false);

			auto phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
			if(phys_comp)
				graph_comp->node->setPosition(phys_comp->position);
		}
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

void GridSystem::place_structure(tdt::uint ent_id, tdt::uint node_id, tdt::uint radius)
{
	auto struct_comp = entities_.get_component<StructureComponent>(ent_id);
	if(!struct_comp)
		return;

	Grid& grid = Grid::instance();
	tdt::uint x, y;
	std::tie(x, y) = GridNodeHelper::get_board_coords(entities_, node_id);
	tdt::uint start_node = grid.get_node(x - radius, y - radius);
	std::tie(x, y) = GridNodeHelper::get_board_coords(entities_, start_node);
	tdt::uint target_node{};

	// This will check if the entire area is free first.
	if(!GridNodeHelper::area_free(entities_, node_id, radius))
		return;

	radius = radius * 2 + 1;
	for(tdt::uint i = 0; i < radius; ++i)
	{
		for(tdt::uint j = 0; j < radius; ++j)
		{
			target_node = grid.get_node(x + i, y + j);
			GridNodeHelper::set_free(entities_, target_node, false);
			GridNodeHelper::set_resident(entities_, target_node, ent_id);
			struct_comp->residences.push_back(target_node);
		}
	}
}

void GridSystem::update_neighbours_(tdt::uint id)
{
	auto comp = entities_.get_component<GridNodeComponent>(id);
	
	if(!comp || comp->resident == Component::NO_ENTITY) // Saves 2 component lookups.
		return;

	auto node_phys = entities_.get_component<PhysicsComponent>(id);
	auto graph = entities_.get_component<GraphicsComponent>(comp->resident);
	auto phys = entities_.get_component<PhysicsComponent>(comp->resident);
	auto align = entities_.get_component<AlignComponent>(comp->resident);
	if(comp && graph && phys && graph->node && graph->entity && align && node_phys)
	{

		auto& neigh = comp->neighbours;
		int active_main_neighbours{0}; // Main neighbours: UP, DOWN, LEFT, RIGHT.
		
		// Only align to other blocks with align or dummy align components.
		auto resident_up = GridNodeHelper::get_resident(entities_, neigh[DIRECTION::UP]);
		auto resident_down = GridNodeHelper::get_resident(entities_, neigh[DIRECTION::DOWN]);
		auto resident_left = GridNodeHelper::get_resident(entities_, neigh[DIRECTION::LEFT]);
		auto resident_right = GridNodeHelper::get_resident(entities_, neigh[DIRECTION::RIGHT]);

		bool dummy_up = entities_.has_component<DummyAlignComponent>(resident_up);
		bool dummy_down = entities_.has_component<DummyAlignComponent>(resident_down);
		bool dummy_left = entities_.has_component<DummyAlignComponent>(resident_left);
		bool dummy_right = entities_.has_component<DummyAlignComponent>(resident_right);
		bool dummy = dummy_up || dummy_down || dummy_left || dummy_right;

		bool up = !GridNodeHelper::is_free(entities_, neigh[DIRECTION::UP])
			      && (entities_.has_component<AlignComponent>(resident_up) || dummy_up);
		bool down = !GridNodeHelper::is_free(entities_, neigh[DIRECTION::DOWN])
			      && (entities_.has_component<AlignComponent>(resident_down) || dummy_down);
		bool left = !GridNodeHelper::is_free(entities_, neigh[DIRECTION::LEFT])
			      && (entities_.has_component<AlignComponent>(resident_left) || dummy_left);
		bool right = !GridNodeHelper::is_free(entities_, neigh[DIRECTION::RIGHT])
			      && (entities_.has_component<AlignComponent>(resident_right) || dummy_right);
		if(up)
			++active_main_neighbours;
		if(down)
			++active_main_neighbours;
		if(left)
			++active_main_neighbours;
		if(right)
			++active_main_neighbours;

		if(active_main_neighbours == 2 && (up && down || left && right)) // Tunnel.
			active_main_neighbours = 5;

		graph->material = align->states[active_main_neighbours].material;
		graph->scale = align->states[active_main_neighbours].scale;

		auto& mesh = align->states[active_main_neighbours].mesh;
		if(dummy)
			graph->mesh = mesh.substr(0, mesh.size() - 5) + "_full.mesh";
		else
			graph->mesh = mesh;

		graph->node->setScale(graph->scale);
		graph->node->detachObject(graph->entity);
		scene_mgr_.destroyEntity(graph->entity);
		graph->entity = scene_mgr_.createEntity(graph->mesh);
		graph->node->attachObject(graph->entity);
		if(graph->material != "NO_MAT")
			graph->entity->setMaterialName(graph->material);
		graph->node->setOrientation(Ogre::Quaternion{}); // Reverses any rotations.
		graph->entity->setRenderingDistance(4000.f);

		Ogre::Vector3 pos{node_phys->position};
		if(active_main_neighbours == 1)
		{ // Lean to the neighbour.
			if(up)
				pos.z -= graph->scale.x;
			else if(down)
				pos.z += graph->scale.x;
			else if(left)
				pos.x -= graph->scale.z / 2;
			else if(right)
				pos.x += graph->scale.z / 2;
		}
		else
			pos += align->states[active_main_neighbours].position_offset;

		phys->half_height = graph->entity->getWorldBoundingBox(true).getHalfSize().y;
		phys->position.x = pos.x;
		phys->position.y = phys->half_height + pos.y;
		phys->position.z = pos.z;
		graph->node->setPosition(phys->position);

		// Rotation for alignment.
		Ogre::Vector3 rotation_axis_y{0.f, 1.f, 0.f};
		Ogre::Degree deg0{0.f};
		Ogre::Degree deg90{90.f};
		Ogre::Degree deg180{180.f};
		Ogre::Degree deg270{270.f};
		switch(active_main_neighbours)
		{
			case 0:
				// No rotation needed.
				break;
			case 1:
				if(left)
					graph->node->rotate(rotation_axis_y, deg180);
				else if(up)
					graph->node->rotate(rotation_axis_y, deg90);
				else if(right)
					graph->node->rotate(rotation_axis_y, deg0);
				else if(down)
					graph->node->rotate(rotation_axis_y, deg270);
				break;
			case 2:
				if(up && left)
					graph->node->rotate(rotation_axis_y, deg0);
				else if(down && left)
					graph->node->rotate(rotation_axis_y, deg90);
				else if(down && right)
					graph->node->rotate(rotation_axis_y, deg180);
				else if(up && right)
					graph->node->rotate(rotation_axis_y, deg270);
				break;
			case 3:
				if(up && right && down)
					graph->node->rotate(rotation_axis_y, deg0);
				else if(up && left && right)
					graph->node->rotate(rotation_axis_y, deg90);
				else if(down && left && up)
					graph->node->rotate(rotation_axis_y, deg180);
				else if(down && right && left)
					graph->node->rotate(rotation_axis_y, deg270);
				break;
			case 4:
				// No rotation needed, only top face used.
				break;
			case 5:
				if(up && down)
					graph->node->rotate(rotation_axis_y, deg90);
				if(right && left)
					graph->node->rotate(rotation_axis_y, deg180);
				break;
			default:
				GUI::instance().get_console().print_text("[ERROR] Wrong neighbour count: " + std::to_string(active_main_neighbours),
														 Console::RED_TEXT);
				break;
		}

		auto sel = entities_.get_component<SelectionComponent>(comp->resident);
		if(sel && sel->marker_type == SELECTION_MARKER_TYPE::SQUARE && active_main_neighbours == 2)
		{
			sel->marker_type = SELECTION_MARKER_TYPE::HALF_SQUARE;
			sel->rotation = deg90; // Needed to overcome the orientation difference of those models.
		}
		else if(sel && sel->marker_type == SELECTION_MARKER_TYPE::HALF_SQUARE && active_main_neighbours != 2)
		{
			sel->marker_type = SELECTION_MARKER_TYPE::SQUARE;
			sel->rotation = deg0;
		}
	}
}
