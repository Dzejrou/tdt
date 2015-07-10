#include "Entity.hpp"

Entity::Entity(std::vector<std::unique_ptr<Entity>>& ent, Ogre::Real x, Ogre::Real y, Ogre::Real z,
               InputComponent* in, PhysicsComponent* ph, GraphicsComponent* gr)
    : input_{in}, physics_{ph}, graphics_{gr},
      state_{ENTITY_STATE::Normal}, entities_{ent}
{
    physics_->set_position(Ogre::Vector3{x, y, z});
}

void Entity::update(Ogre::Real delta)
{
    input_->update(*this, delta);
    physics_->update(*this, delta);
    graphics_->update(*this, delta);
}

std::vector<std::unique_ptr<Entity>>& Entity::get_entity_list()
{
    return entities_;
}

const ENTITY_STATE& Entity::get_state() const
{
    return state_;
}

void Entity::set_state(ENTITY_STATE s)
{
    state_ = s;
}