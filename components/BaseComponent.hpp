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
        bool has_moved() const;
        void set_moved(bool);
    protected:
        Ogre::Vector3 position_{0, 0, 0};
        bool moved_{false};
};

class GraphicsComponent
{
    public:
        virtual ~GraphicsComponent() {}
        virtual void update(Entity&, Ogre::Real) = 0;
        const Ogre::AxisAlignedBox& get_bounding_box() const;
    protected:
        Ogre::SceneNode* node_;
        Ogre::Entity* entity_;
};