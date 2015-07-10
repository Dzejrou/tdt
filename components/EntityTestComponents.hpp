#pragma once

#include <Ogre.h>

#include "BaseComponent.hpp"

class EntityTestInputComponent : public InputComponent
{
    public:
        void update(Entity&, Ogre::Real) override;
};

class EntityTestPhysicsComponent : public PhysicsComponent
{
    public:
        void update(Entity&, Ogre::Real) override;
};

class EntityTestGraphicsComponent : public GraphicsComponent
{
    public:
        EntityTestGraphicsComponent(Ogre::SceneManager&);
        ~EntityTestGraphicsComponent() {}
        void update(Entity&, Ogre::Real) override;
};