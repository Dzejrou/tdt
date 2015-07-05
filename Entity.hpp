#pragma once

#include <memory>
#include <array>

#include "components/Component.hpp"

class Entity
{
    public:
        Entity(InputComponent*, PhysicsComponent*, GraphicsComponent*);
        void update();
    private:
        std::unique_ptr<InputComponent> input_;
        std::unique_ptr<PhysicsComponent> physics_;
        std::unique_ptr<GraphicsComponent> graphics_;

        float x_, y_, z_;
};