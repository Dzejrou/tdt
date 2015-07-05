#include "Entity.hpp"

Entity::Entity(InputComponent* in, PhysicsComponent* ph, GraphicsComponent* gr,
               int x, int y, int z)
    : input_{in}, physics_{ph}, graphics_{gr},
      x_{x}, y_{y}, z_{z}
{ /* DUMMY BODY */ }

void Entity::update()
{
    input_->update(*this);
    physics_->update(*this);
    graphics_->update(*this);
}

std::tuple<float, float, float> Entity::get_position()
{
    return std::make_tuple(x_, y_, z_);
}