#pragma once

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
    void update(Entity&, Ogre::Real) override;
};