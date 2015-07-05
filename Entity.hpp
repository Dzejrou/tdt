#pragma once

#include <memory>
#include <tuple>

#include "components/Component.hpp"

class Entity
{
    public:
        Entity(InputComponent*, PhysicsComponent*, GraphicsComponent*, int, int, int);
        ~Entity() { /* DUMMY BODY */ }
        void update();

        std::tuple<float, float, float> get_position();
    private:
        std::unique_ptr<InputComponent> input_;
        std::unique_ptr<PhysicsComponent> physics_;
        std::unique_ptr<GraphicsComponent> graphics_;

        float x_, y_, z_;
};