#pragma once

#include <Ogre.h>


// Forward declaration.
class Entity;

class GraphicsComponent
{
    public:
        virtual ~GraphicsComponent() {}
        virtual void update(Entity&, Ogre::Real) = 0;
};

class PhysicsComponent
{
    public:
        virtual ~PhysicsComponent() {}
        virtual void update(Entity&, Ogre::Real) = 0;
};

class InputComponent
{
    public:
        virtual ~InputComponent() {}
        virtual void update(Entity&, Ogre::Real) = 0;
};