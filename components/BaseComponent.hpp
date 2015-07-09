#pragma once

#include <Ogre.h>
#include <tuple>

// Forward declaration.
class Entity;

class InputComponent
{
    public:
        virtual ~InputComponent() {}
        virtual void update(Entity&, Ogre::Real) = 0;
};

class PhysicsComponent
{
    using coords = std::tuple<Ogre::Real, Ogre::Real, Ogre::Real>;
    public:
        virtual ~PhysicsComponent() {}
        virtual void update(Entity&, Ogre::Real) = 0;
        Ogre::Vector3 get_position() const;
        void set_position(const Ogre::Vector3&);
    protected:
        Ogre::Vector3 position_;
};

class GraphicsComponent
{
    public:
        virtual ~GraphicsComponent() {}
        virtual void update(Entity&, Ogre::Real) = 0;
        virtual void init(Ogre::SceneManager*) = 0;
    protected:
        Ogre::SceneNode* node_;
        Ogre::Entity* entity_;
};