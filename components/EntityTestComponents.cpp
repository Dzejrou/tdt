#include "EntityTestComponents.hpp"
#include "../Entity.hpp"

void EntityTestInputComponent::update(Entity& entity, Ogre::Real delta)
{
}

void EntityTestPhysicsComponent::update(Entity &, Ogre::Real)
{

}

EntityTestGraphicsComponent::EntityTestGraphicsComponent(Ogre::SceneManager& scene)
{
    entity_ = scene.createEntity("ogrehead.mesh");
    node_ = scene.getRootSceneNode()->createChildSceneNode();
    node_->attachObject(entity_);
}

void EntityTestGraphicsComponent::update(Entity& entity, Ogre::Real delta)
{
    if(entity.get_component<PhysicsComponent>()->has_moved())
    {
        node_->setPosition(entity.get_component<PhysicsComponent>()->get_position());
        entity.get_component<PhysicsComponent>()->set_moved(false);
    }
}
