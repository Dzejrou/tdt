#pragma once

#include <Ogre.h>

#include "BaseComponent.hpp"

class EntityTestInputComponent : public InputComponent
{
    void update(Entity&, Ogre::Real) override;
};

class EntityTestPhysicsComponent : public PhysicsComponent
{
    void update(Entity&, Ogre::Real) override;
};

class EntityTestGraphicsComponent : public GraphicsComponent
{
    EntityTestGraphicsComponent();
    ~EntityTestGraphicsComponent() {}
    void update(Entity&, Ogre::Real) override;
    void init(Ogre::SceneManager*) override;
};