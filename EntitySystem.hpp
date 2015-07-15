#pragma once

#include <Ogre.h>
#include <map>
#include <stdexcept>
#include <string>

#include "Components.hpp"
#include "lppscript\LppScript.hpp"

class EntitySystem
{
#define COMP_COUNT 8
	public:
		/**
		 * Brief: Constructor.
		 * Param: Reference to the game's scene manager used to create nodes and entities.
		 */
		EntitySystem(Ogre::SceneManager&);

		/**
		 * Brief: Destructor.
		 */
		~EntitySystem() { /* DUMMY BODY */ }

		/**
		 * Brief: Returns first available entity id.
		 */
		std::size_t get_new_id() const;

		/**
		 * Brief: Removes all entities that have no components.
		 */
		void cleanup();

		/**
		 * Brief: Creates a new entity from a blueprint.
		 * Param: Name of the Lua table containing the entity blueprint.
		 */
		std::size_t create_entity(std::string);

		/**
		 * Brief: Removes an entity from the system, thus killing/destroying it.
		 * Param: ID of the entity.
		 */
		void destroy_entity(std::size_t);

		/**
		 * Breif: Returns const reference to the component list, so that it can
		 *        be used to iterate over all entities.
		 */
		const std::map<std::size_t, std::bitset<COMP_COUNT>>& get_component_list() const;
		
		/**
		 * Brief: Tests whether a given entity has a component specialized by the
		 *	      template argument.
		 * Param: ID of the entity being checked.
		 * Note: VS2015RC does not let me use variadic templates with recursion to check multiple
		 *       components for some reason, investigate!
		 */
		template<typename COMP>
		bool has_component(std::size_t id) const
		{
			return components_.find(id)->second.test(COMP::type);
		}

		/**
		 * Brief: Returns a reference to the component specified by the template argument of a given entity.
		 * Param: ID of the entity whose component we ask for.
		 */
		template<typename COMP>
		COMP& get_component(std::size_t id)
		{
			auto it = get_component_container<COMP>().find(id);
			if(it != get_component_container<COMP>().end())
				return it->second;
			else
				throw std::runtime_error("[Error][EntitySystem] Trying to retrieve a non-existing component.");
		}

		/**
		 * Brief: Changes a component (type specified by template argument) of and entity or assigns a new
		 *		  component it that entity didn't have it.
		 * Param: ID of the entity.
		 * Param: Component to be assigned.
		 */
		template<typename COMP>
		void set_component(std::size_t id, COMP comp)
		{
			auto it = get_component_container<COMP>().find(id);
			if(it != get_component_container<COMP>().end())
				it->second = comp;
			else
			{
				get_component_container<COMP>().emplace(std::make_pair(id, std::move(comp)));
				components_[id].set(COMP::type); // Notify of the presence of this new component.
			}
		}
	private:
		/**
		 * Brief: Returns the map associated with the component specified by the template argument.
		 */
		template<typename COMP>
		std::map<std::size_t, COMP>& get_component_container()
		{ // Will have specializations.
			throw std::runtime_error("[Error][EntitySystem] Trying to access container of a non-existent component: "
								     + std::to_string(COMP::type));
		}

		/**
		 * Brief: Loads a component from a Lua script.
		 * Param: ID of the entity.
		 * Param: Name of the table containing the component.
		 */
		template<typename COMP>
		void load_component(std::size_t id, std::string table_name)
		{ // Will have specializations.
			throw std::runtime_error("[Error][EntitySystem] Trying to load a non-existent component: "
								     + std::to_string(COMP::type));
		}

		// Contains bitsets describing component availability.
		std::map<std::size_t, std::bitset<COMP_COUNT>> components_;

		// Contain components specified by the entity ID.
		std::map<std::size_t, PhysicsComponent> physics_;
		std::map<std::size_t, HealthComponent> health_;
		std::map<std::size_t, AIComponent> ai_;
		std::map<std::size_t, GraphicsComponent> graphics_;
		std::map<std::size_t, MovementComponent> movement_;
		std::map<std::size_t, CombatComponent> combat_;
		std::map<std::size_t, EventComponent> event_;

		// To create nodes and entities.
		Ogre::SceneManager& scene_;
};

/**
 * Specializations of the EntitySystem::get_component_container method.
 */
template<>
inline std::map<std::size_t, PhysicsComponent>& EntitySystem::get_component_container<PhysicsComponent>()
{
	return physics_;
}

template<>
inline std::map<std::size_t, HealthComponent>& EntitySystem::get_component_container<HealthComponent>()
{
	return health_;
}

template<>
inline std::map<std::size_t, AIComponent>& EntitySystem::get_component_container<AIComponent>()
{
	return ai_;
}

template<>
inline std::map<std::size_t, GraphicsComponent>& EntitySystem::get_component_container<GraphicsComponent>()
{
	return graphics_;
}

template<>
inline std::map<std::size_t, MovementComponent>& EntitySystem::get_component_container<MovementComponent>()
{
	return movement_;
}

template<>
inline std::map<std::size_t, CombatComponent>& EntitySystem::get_component_container<CombatComponent>()
{
	return combat_;
}

template<>
inline std::map<std::size_t, EventComponent>& EntitySystem::get_component_container<EventComponent>()
{
	return event_;
}

/**
 * Specializations of the EntitySystem::load_component method.
 */
template<>
inline void EntitySystem::load_component<PhysicsComponent>(std::size_t id, std::string table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	bool solid = script.get<bool>(table_name + ".PhysicsComponent.solid");
	physics_.emplace(std::make_pair(id, PhysicsComponent{solid}));
}

template<>
inline void EntitySystem::load_component<HealthComponent>(std::size_t id, std::string table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	int max = script.get<int>(table_name + ".HealthComponent.max_hp");
	int reg = script.get<int>(table_name + ".HealthComponent.regen");
	int def = script.get<int>(table_name + ".HealthComponent.defense");
	health_.emplace(std::make_pair(id, HealthComponent(max, reg, def)));
}

template<>
inline void EntitySystem::load_component<AIComponent>(std::size_t id, std::string table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	std::string blueprint = script.get<std::string>(table_name + ".AIComponent.blueprint");
	int faction = script.get<int>(table_name + ".AIComponent.faction");
	ai_.emplace(std::make_pair(id, AIComponent{blueprint, faction}));

	// Call init.
	script.call<void, int>(blueprint + ".init", id);
}

template<>
inline void EntitySystem::load_component<GraphicsComponent>(std::size_t id, std::string table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	std::string mesh = script.get<std::string>(table_name + ".GraphicsComponent.mesh");
	std::string mat = script.get<std::string>(table_name + ".GraphicsComponent.material");
	graphics_.emplace(std::make_pair(id, GraphicsComponent{mesh, mat}));
}

template<>
inline void EntitySystem::load_component<MovementComponent>(std::size_t id, std::string table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	float speed = script.get<float>(table_name + ".MovementComponent.speed_modifier");
	movement_.emplace(std::make_pair(id, MovementComponent{speed}));
}

template<>
inline void EntitySystem::load_component<CombatComponent>(std::size_t id, std::string table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	int range = script.get<int>(table_name + ".CombatComponent.range");
	int min = script.get<int>(table_name + ".CombatComponent.min_dmg");
	int max = script.get<int>(table_name + ".CombatComponent.max_dmg");
	int a1 = script.get<int>(table_name + ".CombatComponent.atk_1");
	int a2 = script.get<int>(table_name + ".CombatComponent.atk_2");
	combat_.emplace(std::make_pair(id, CombatComponent(range, min, max, a1, a2)));
}

template<>
inline void EntitySystem::load_component<EventComponent>(std::size_t id, std::string table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	event_.emplace(std::make_pair(id, EventComponent{}));
}