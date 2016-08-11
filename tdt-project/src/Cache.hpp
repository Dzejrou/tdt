#pragma once

#include <utility>
#include <Typedefs.hpp>
#include <Components.hpp>

#define CACHE_ALLOWED 1

#if CACHE_ALLOWED == 1
/**
 * This macro is used in helpers to load a component either from cache or an entity system.
 * Note that this requires a variable "cache" of type *Cache where * is equal to the name of the component
 * (as seen above).
 */
#define GET_COMPONENT(ID, ENTS, COMP, TYPE) if(cache.first == ID) COMP = cache.second; else { COMP = ENTS.get_component<TYPE>(ID); cache.first = ID; cache.second = COMP; }
#else
/**
 * This macro has the exact same functionality as the old component loading and is used
 * for simple activation/deactivation of the cache.
 */
#define GET_COMPONENT(ID, ENTS, COMP, TYPE) COMP = ENTS.get_component<TYPE>(ID);
#endif

namespace tdt
{
	namespace cache
	{
		using ActivationCache      = std::pair<tdt::uint, ActivationComponent*>;
		using AICache              = std::pair<tdt::uint, AIComponent*>;
		using AlignCache           = std::pair<tdt::uint, AlignComponent*>;
		using AnimationCache       = std::pair<tdt::uint, AnimationComponent*>;
		using CombatCache          = std::pair<tdt::uint, CombatComponent*>;
		using CommandCache         = std::pair<tdt::uint, CommandComponent*>;
		using ConstructorCache     = std::pair<tdt::uint, ConstructorComponent*>;
		using CounterCache         = std::pair<tdt::uint, CounterComponent*>;
		using DestructorCache      = std::pair<tdt::uint, DestructorComponent*>;
		using EventHandlerCache    = std::pair<tdt::uint, EventHandlerComponent*>;
		using EventCache           = std::pair<tdt::uint, EventComponent*>;
		using ExperienceValueCache = std::pair<tdt::uint, ExperienceValueComponent*>;
		using ExplosionCache       = std::pair<tdt::uint, ExplosionComponent*>;
		using FactionCache         = std::pair<tdt::uint, FactionComponent*>;
		using GoldCache            = std::pair<tdt::uint, GoldComponent*>;
		using GraphicsCache        = std::pair<tdt::uint, GraphicsComponent*>;
		using GridNodeCache        = std::pair<tdt::uint, GridNodeComponent*>;
		using HealthCache          = std::pair<tdt::uint, HealthComponent*>;
		using HomingCache          = std::pair<tdt::uint, HomingComponent*>;
		using InputCache           = std::pair<tdt::uint, InputComponent*>;
		using LightCache           = std::pair<tdt::uint, LightComponent*>;
		using LimitedLifeSpanCache = std::pair<tdt::uint, LimitedLifeSpanComponent*>;
		using ManaCrystalCache     = std::pair<tdt::uint, ManaCrystalComponent*>;
		using ManaCache            = std::pair<tdt::uint, ManaComponent*>;
		using MovementCache        = std::pair<tdt::uint, MovementComponent*>;
		using NameCache            = std::pair<tdt::uint, NameComponent*>;
		using NotificationCache    = std::pair<tdt::uint, NotificationComponent*>;
		using OnHitCache           = std::pair<tdt::uint, OnHitComponent*>;
		using PathfindingCache     = std::pair<tdt::uint, PathfindingComponent*>;
		using PhysicsCache         = std::pair<tdt::uint, PhysicsComponent*>;
		using PriceCache           = std::pair<tdt::uint, PriceComponent*>;
		using ProductCache         = std::pair<tdt::uint, ProductComponent*>;
		using ProductionCache      = std::pair<tdt::uint, ProductionComponent*>;
		using SelectionCache       = std::pair<tdt::uint, SelectionComponent*>;
		using SpellCache           = std::pair<tdt::uint, SpellComponent*>;
		using StructureCache       = std::pair<tdt::uint, StructureComponent*>;
		using TaskHandlerCache     = std::pair<tdt::uint, TaskHandlerComponent*>;
		using TaskCache            = std::pair<tdt::uint, TaskComponent*>;
		using TimeCache            = std::pair<tdt::uint, TimeComponent*>;
		using TriggerCache         = std::pair<tdt::uint, TriggerComponent*>;
		using UpgradeCache         = std::pair<tdt::uint, UpgradeComponent*>;
	}
}
