#include "BaseComponent.hpp"

Ogre::Vector3 PhysicsComponent::get_position() const
{
    return position_;
}

void PhysicsComponent::set_position(const Ogre::Vector3& coord)
{
    position_ = coord;
}