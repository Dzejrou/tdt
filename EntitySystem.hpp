#pragma once

#include <map>
#include <exception>

#include "Components.hpp"

class EntitySystem
{
	public:
		EntitySystem();

		std::size_t get_new_id() const;
		
		/**
		 * Brief: Recursive method testing if an entity has all of the components
		 *        passed as template arguments.
		 * Param: ID of the entity being checked.
		 */
		template<typename COMP, typename... COMPS>
		bool has_components(std::size_t id)
		{
			return has_component<COMP>(id) &&
				   has_components<COMPS...>(id);
		}

		/**
		 * Brief: Tests whether a given entity has a component specialized by the
		 *	      template argument.
		 * Param: ID of the entity being checked.
		 */
		template<typename COMP>
		bool has_component(std::size_t id) const
		{
			return components_[id].test(COMP::type);
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
				throw std::exception{"[Error][EntitySystem] Trying to retrieve a non-existing component of "
									 + "type " + COMP::type + " from entity #" + std::to_string(id)};
		}

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
		template<typename COMP>
		std::map<std::size_t, COMP>& get_component_container()
		{ // Will have specializations.
			throw std::exception{"[Error][EntitySystem] Trying to access component container of a non-existent entity."};
		}

		std::map<std::size_t, std::bitset<8>> components_;

		std::map<std::size_t, PhysicsComponent> physics_;
		std::map<std::size_t, HealthComponent> health_;
		std::map<std::size_t, AIComponent> ai_;
		std::map<std::size_t, GraphicsComponent> graphics_;
		std::map<std::size_t, MovementComponent> movement_;
		std::map<std::size_t, CombatComponent> combat_;
		std::map<std::size_t, EventComponent> event_;
};

/**
 * Specializations of the EntitySystem::get_component_container method.
 */
template<>
std::map<std::size_t, PhysicsComponent>& EntitySystem::get_component_container<PhysicsComponent>()
{
	return physics_;
}

template<>
std::map<std::size_t, HealthComponent>& EntitySystem::get_component_container<HealthComponent>()
{
	return health_;
}

template<>
std::map<std::size_t, AIComponent>& EntitySystem::get_component_container<AIComponent>()
{
	return ai_;
}

template<>
std::map<std::size_t, GraphicsComponent>& EntitySystem::get_component_container<GraphicsComponent>()
{
	return graphics_;
}

template<>
std::map<std::size_t, MovementComponent>& EntitySystem::get_component_container<MovementComponent>()
{
	return movement_;
}

template<>
std::map<std::size_t, CombatComponent>& EntitySystem::get_component_container<CombatComponent>()
{
	return combat_;
}

template<>
std::map<std::size_t, EventComponent>& EntitySystem::get_component_container<EventComponent>()
{
	return event_;
}
