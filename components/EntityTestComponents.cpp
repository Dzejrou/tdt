#include "EntityTestComponents.hpp"

void EntityTestInputComponent::update(Entity &, Ogre::Real)
{

}

void EntityTestPhysicsComponent::update(Entity &, Ogre::Real)
{

}

EntityTestGraphicsComponent::EntityTestGraphicsComponent()
{

}

void EntityTestGraphicsComponent::update(Entity& entity, Ogre::Real delta)
{
    node_->setPosition(entity.get_component<PhysicsComponent>.get_position());
}

void EntityTestGraphicsComponent::init(Ogre::SceneManager* scene)
{
    entity_ = scene->createEntity("ogrehead.mesh");
    node_ = scene->getRootSceneNode()->createChildSceneNode();
    node_->attachObject(entity_);
}
