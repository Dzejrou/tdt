#include "GridSystem.hpp"

GridSystem::GridSystem(EntitySystem& ents, Ogre::SceneManager& scene)
	: entities_{ents}, scene_mgr_{scene}
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

std::size_t GridSystem::add_node(Ogre::Real x, Ogre::Real z)
{
	auto id = entities_.create_entity();
	auto& node_comp = entities_.add_component<GridNodeComponent>(id);
	auto& graph_comp = entities_.add_component<GraphicsComponent>(id);
	auto& phys_comp = entities_.add_component<PhysicsComponent>(id);

	phys_comp.position = Ogre::Vector3{x, 20, z};
	graph_comp.mesh = "cube.mesh";
	graph_comp.material = "colour/red";
	entities_.init_graphics_component(id); // Creates entity and node.
	graph_comp.node->setScale(10, 20, 10);
	graph_comp.node->setPosition(phys_comp.position);

	return id;
}

std::size_t GridSystem::add_line(std::size_t id1, std::size_t id2)
{
	auto id = entities_.create_entity();
	auto& line_comp = entities_.add_component<GridLineComponent>(id);
	auto& graph_comp = entities_.add_component<GraphicsComponent>(id);

	line_comp.start_id = id1;
	line_comp.end_id = id2;
	auto pos_start = entities_.get_component<PhysicsComponent>(id1).position;
	auto pos_end = entities_.get_component<PhysicsComponent>(id2).position;
	line_comp.distance = pos_start.distance(pos_end);
	line_comp.line.reset(new Line{pos_start, pos_end});

	graph_comp.entity = line_comp.line.get();
	graph_comp.node = scene_mgr_.getRootSceneNode()->createChildSceneNode();
	graph_comp.node->attachObject(graph_comp.entity);
	graph_comp.material = "colour/blue";
	graph_comp.mesh = "LINE";
	graph_comp.visible = true;
	graph_comp.node->setVisible(true);

	return std::size_t();
}
