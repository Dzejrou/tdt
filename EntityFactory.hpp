#pragma once

#include "components/Components.hpp"
#include "Entity.hpp"

class EntityFactory
{
    public:
        EntityFactory(std::vector<std::unique_ptr<Entity>>&, Ogre::SceneManager*);

        template<typename T>
        Entity* create_entity(Ogre::Real x = 0, Ogre::Real y = 0, Ogre::Real z = 0)
        { // TODO: change default spawn point when possible.
            return new Entity{
                entities_, x, y, z,
                new T::InputComponent{}, new T::PhysicsComponent{}, new T::GraphicsComponent{scene_mgr_}
            };
        }

    public:
        std::vector<std::unique_ptr<Entity>>& entities_;
        Ogre::SceneManager& scene_mgr_;
};