#include "GraphicsHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void GraphicsHelper::look_at(EntitySystem& ents, std::size_t id1, std::size_t id2)
{
	auto comp1 = ents.get_component<GraphicsComponent>(id1);
	auto comp2 = ents.get_component<PhysicsComponent>(id2);
	if(comp1 && comp2)
	{
		auto& target_pos = comp2->position;
		comp1->node->lookAt(
				Ogre::Vector3{target_pos.x, comp1->node->getPosition().y, target_pos.z},
				Ogre::Node::TransformSpace::TS_WORLD,
				Ogre::Vector3::UNIT_Z
			);
	}
}

void GraphicsHelper::rotate(EntitySystem& ents, std::size_t id, Ogre::Real delta)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		comp->node->rotate(Ogre::Vector3{0, 1, 0}, Ogre::Radian{delta});
}

const Ogre::AxisAlignedBox& GraphicsHelper::get_bounds(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->entity->getWorldBoundingBox();
	else
		return Ogre::AxisAlignedBox::BOX_NULL; // TODO: Test this vs BOX_INFINITE.
}

bool GraphicsHelper::collide(EntitySystem& ents, std::size_t id1, std::size_t id2)
{
	return get_bounds(ents, id1).intersects(get_bounds(ents, id2));
}