#include "BaseComponent.hpp"

Ogre::Vector3 PhysicsComponent::get_position() const
{
    return position_;
}

void PhysicsComponent::set_position(const Ogre::Vector3& coord)
{
    moved_ = true;
    position_ = coord;
}

void PhysicsComponent::set_moved(bool mov)
{
    moved_ = mov;
}

bool PhysicsComponent::has_moved() const
{
    return moved_;
}

const Ogre::AxisAlignedBox & GraphicsComponent::get_bounding_box() const
{
    return entity_->getBoundingBox();
}
