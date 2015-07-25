#include "GridSystem.hpp"

GridSystem::GridSystem(EntitySystem& ents, Ogre::SceneManager& scene)
	: entities_{ents}, scene_mgr_{scene}
{ /* DUMMY BODY */ }

void GridSystem::update(Ogre::Real)
{
}

bool GridSystem::is_valid(std::size_t) const
{
	return false;
}

void GridSystem::add_node(Ogre::Real x, Ogre::Real z)
{
	auto id = entities_.create_entity();
	auto& node_comp = entities_.add_component<GridNodeComponent>(id);
	auto& graph_comp = entities_.add_component<GraphicsComponent>(id);
}
