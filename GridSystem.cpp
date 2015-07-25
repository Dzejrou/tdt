#include "GridSystem.hpp"

GridSystem::GridSystem(EntitySystem& ents, Ogre::SceneManager& scene)
	: entities_{ents}, scene_mgr_{scene}
{
	create_block_mesh();
}

void GridSystem::update(Ogre::Real)
{
}

bool GridSystem::is_valid(std::size_t) const
{
	return false;
}

void GridSystem::create_block_mesh()
{
	Ogre::ManualObject* block = scene_mgr_.createManualObject("block_object");

	//block->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	block->begin("colour/red", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	// Bottom quad.
	block->position(-.5f,  0.f, -.5f);
	block->normal(Ogre::Vector3::NEGATIVE_UNIT_Y);
	block->position( .5f,  0.f, -.5f);
	block->normal(Ogre::Vector3::NEGATIVE_UNIT_Y);
	block->position(-.5f,  0.f,  .5f);
	block->normal(Ogre::Vector3::NEGATIVE_UNIT_Y);
	block->position( .5f,  0.f,  .5f);
	block->normal(Ogre::Vector3::NEGATIVE_UNIT_Y);
	// Top quad.
	block->position(-.5f,  1.f, -.5f);
	block->normal(Ogre::Vector3::UNIT_Y);
	block->position( .5f,  1.f, -.5f);
	block->normal(Ogre::Vector3::UNIT_Y);
	block->position(-.5f,  1.f,  .5f);
	block->normal(Ogre::Vector3::UNIT_Y);
	block->position( .5f,  1.f,  .5f);
	block->normal(Ogre::Vector3::UNIT_Y);
	// Left quad.

	// Right quad.

	// Side centres.
	block->position(-.5f,  .5f,  0.f);
	block->normal(Ogre::Vector3::NEGATIVE_UNIT_X);
	block->position( .5f,  .5f,  0.f);
	block->normal(Ogre::Vector3::UNIT_X);
	block->position( 0.f,  .5f,  .5f);
	block->normal(Ogre::Vector3::UNIT_Z);
	block->position( 0.f,  .5f, -.5f);
	block->normal(Ogre::Vector3::NEGATIVE_UNIT_Z);
	// Top/Bottom centres.
	block->position( 0.f,  1.f,  0.f);
	block->normal(Ogre::Vector3::UNIT_Y);
	block->position( 0.f,  0.f,  0.f);
	block->normal(Ogre::Vector3::NEGATIVE_UNIT_Y);

	// Triangles.
	// Bottom.
	block->triangle(0, 13, 1);
	block->triangle(1, 13, 3);
	block->triangle(3, 13, 2);
	block->triangle(2, 13, 3);
	// Front.
	block->triangle(2, 10, 3);
	block->triangle(3, 10, 7);
	block->triangle(7, 10, 6);
	block->triangle(6, 10, 2);
	// Back.
	block->triangle(0, 11, 1);
	block->triangle(1, 11, 5);
	block->triangle(5, 11, 4);
	block->triangle(4, 11, 0);
	// Top.
	block->triangle(4, 12, 5);
	block->triangle(5, 12, 7);
	block->triangle(7, 12, 6);
	block->triangle(6, 12, 4);
	// Left.
	block->triangle(2, 8, 0);
	block->triangle(0, 8, 4);
	block->triangle(4, 8, 6);
	block->triangle(6, 8, 2);
	// Right.
	block->triangle(3, 9, 1);
	block->triangle(1, 9, 5);
	block->triangle(5, 9, 7);
	block->triangle(7, 9, 3);
	block->end();

	block->convertToMesh("block.mesh");
}
