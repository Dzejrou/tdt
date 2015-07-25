#include "GridSystem.hpp"

GridSystem::GridSystem(EntitySystem& ents, Ogre::SceneManager& scene)
	: entities_{ents}, scene_mgr_{scene}
{
	create_block_mesh();
}

void GridSystem::update(Ogre::Real)
{
}

bool GridSystem::is_valid(std::size_t)
{
	return false;
}

void GridSystem::create_block_mesh()
{
	Ogre::ManualObject* block = scene_mgr_.createManualObject("block_object");

	block->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);

	block->end();
}
