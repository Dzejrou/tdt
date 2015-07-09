#pragma once

#include "components/Components.hpp"
#include "Entity.hpp"

class EntityFactory
{
    template<typename T>
    static Entity* create_entity(std::vector<Entity*> ents, Ogre::Real x = 0, Ogre::Real y = 0, Ogre::Real z = 0)
    { // TODO: change default spawn point when possible.
        return new Entity{
            ents, x, y, z,
            new T::InputComponent, new T::PhysicsComponent, new T::GraphicsComponent
        }
    }
};