#include "Entity.hpp"

Entity::Entity(std::vector<Entity>& ent, Ogre::Real x, Ogre::Real y, Ogre::Real z,
               InputComponent* in, PhysicsComponent* ph, GraphicsComponent* gr)
    : input_{in}, physics_{ph}, graphics_{gr},
      x_{x}, y_{y}, z_{z}, node_{nullptr}, entity_{nullptr},
      state_{ENTITY_STATE::Normal}, entities_{ent}
{ /* DUMMY BODY */ }

Entity::Entity(const Entity& other)
    : entities_{other.entities_} // TODO: Complete the copy constructor.
{
    // ...
}

void Entity::update(Ogre::Real delta)
{
    input_->update(*this, delta);
    physics_->update(*this, delta);
    graphics_->update(*this, delta);
}

auto Entity::get_position() const -> coords
{
    return std::make_tuple(x_, y_, z_);
}

void Entity::set_position(const coords& coord)
{
    std::tie(x_, y_, z_) = coord;
}

Ogre::SceneNode& Entity::get_node()
{
    return *node_;
}

std::vector<Entity>& Entity::get_entity_list()
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

const Ogre::AxisAlignedBox & Entity::get_bounding_box()
{
    return entity_->getBoundingBox();
}
