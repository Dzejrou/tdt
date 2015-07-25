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