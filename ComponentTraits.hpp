#pragma once

#include "Components.hpp"

/**
 * This group of structs allows simple translation of an integer to a
 * component type that belongs to that component id.
 */
template<int N>
struct ComponentType {};

template<>
struct ComponentType<0>
{
	using value = PhysicsComponent;
};

template<>
struct ComponentType<1>
{
	using value = HealthComponent;
};

template<>
struct ComponentType<2>
{
	using value = AIComponent;
};

template<>
struct ComponentType<3>
{
	using value = GraphicsComponent;
};

template<>
struct ComponentType<4>
{
	using value = MovementComponent;
};

template<>
struct ComponentType<5>
{
	using value = CombatComponent;
};

template<>
struct ComponentType<6>
{
	using value = EventComponent;
};

template<>
struct ComponentType<7>
{
	using value = InputComponent;
};

template<>
struct ComponentType<8>
{
	using value = TimeComponent;
};

template<>
struct ComponentType<9>
{
	using value = ManaComponent;
};

template<>
struct ComponentType<10>
{
	using value = SpellComponent;
};

template<>
struct ComponentType<11>
{
	using value = ProductionComponent;
};
