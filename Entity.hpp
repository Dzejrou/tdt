#pragma once

#include <memory>
#include <tuple>
#include <exception>

#include <Ogre.h>

#include "components/Component.hpp"

enum class ENTITY_STATE
{
    Normal
};

class Entity
{
    using coords = std::tuple<Ogre::Real, Ogre::Real, Ogre::Real>;
    public:
        Entity(std::vector<Entity>&, Ogre::Real, Ogre::Real, Ogre::Real,
               InputComponent*, PhysicsComponent*, GraphicsComponent*);
        Entity(const Entity&);
        ~Entity() { /* DUMMY BODY */ }
        void update(Ogre::Real);

        coords get_position() const;
        void set_position(const coords&);

        template<typename T>
        T* get_component()
        { // Will have specializations.
            throw std::exception{"[Error] Trying to get a component without method specializaton."};
        }

        template<typename T>
        void set_component(T*)
        { // Will have specializations.
            throw std::exception{"[Error] Trying to set a component without method specializaton."};
        }

        Ogre::SceneNode& get_node();
        std::vector<Entity>& get_entity_list();

        const ENTITY_STATE& get_state() const;
        void set_state(ENTITY_STATE);

    private:
        std::unique_ptr<InputComponent> input_;
        std::unique_ptr<PhysicsComponent> physics_;
        std::unique_ptr<GraphicsComponent> graphics_;

        Ogre::Real x_, y_, z_;
        Ogre::SceneNode* node_;
        ENTITY_STATE state_;
        std::vector<Entity>& entities_;
};



/**
 * Specializations of Entity::get_component used for easier access to
 * the entity's components.
 */
template<>
inline InputComponent* Entity::get_component<InputComponent>()
{
    return input_.get();
}

template<>
inline PhysicsComponent* Entity::get_component<PhysicsComponent>()
{
    return physics_.get();
}

template<>
inline GraphicsComponent* Entity::get_component<GraphicsComponent>()
{
    return graphics_.get();
}



/**
 * Specializations of Entity::set_component for easier setting of the
 * entity's components.
 */
template<>
inline void Entity::set_component<InputComponent>(InputComponent* comp)
{
    input_.reset(comp);
}

template<>
inline void Entity::set_component<PhysicsComponent>(PhysicsComponent* comp)
{
    physics_.reset(comp);
}

template<>
inline void Entity::set_component<GraphicsComponent>(GraphicsComponent* comp)
{
    graphics_.reset(comp);
}