#pragma once

#include <Ogre.h>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "Components.hpp"
#include "lppscript\LppScript.hpp"

/**
 * The EntitySystem class handles everything related to entities, like addition and removal of components,
 * testing if an entity has a component or retrieval of components belonging to particular entities.
 */
class EntitySystem
{
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
		 * Brief: Removes all entities that have no components and individual components marked
		 *        for deletion from their entities (this is used so that the Lua code does not 
		 *        delete an entity/a component from a container while C++ iterates over it).
		 */
		void cleanup();

		/**
		 * Brief: Creates a new entity from a blueprint.
		 * Param: Name of the Lua table containing the entity blueprint.
		 */
		std::size_t create_entity(std::string = "");

		/**
		 * Brief: Removes an entity from the system, thus killing/destroying it.
		 * Param: ID of the entity.
		 */
		void destroy_entity(std::size_t);

		/**
		 * Breif: Returns const reference to the component list, so that it can
		 *        be used to iterate over all entities.
		 */
		const std::map<std::size_t, std::bitset<Component::count>>& get_component_list() const;
		
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
			auto& comp = entities_.find(id);
			if(comp != entities_.end())
				return comp->second.test(COMP::type);
			else
				return false;
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
				entities_[id].set(COMP::type); // Notify of the presence of this new component.
			}
		}

		/**
		 * Brief: Returns the map associated with the component specified by the template argument.
		 */
		template<typename COMP>
		std::map<std::size_t, COMP>& get_component_container();

		/**
		 * Brief: Adds a components to the given enetity using it's default constructor (all values have
		 *        to be set afterwards). Returns reference to the newly created component.
		 * Param: ID of the entity.
		 */
		template<typename COMP>
		COMP& add_component(std::size_t id)
		{
			auto res = get_component_container<COMP>().emplace(std::make_pair(id, COMP{}));

			// Set the flag.
			auto it = entities_.find(id);
			if(it != entities_.end())
				it->second.set(COMP::type, true);

			if(res.second)
				return res.first->second;
			else
				throw std::runtime_error("[Error][EntitySystem] Could not add component of type " +
										 std::to_string(COMP::type) + "to entity #" + std::to_string(id) + ".");
		}

		/**
		 * Brief: Allows to add a component based on it's ID.
		 * Param: ID of the entity.
		 * Param: ID of the component.
		 */
		void add_component(std::size_t, int);

		/**
		 * Brief: Marks a component (specified by template argument) for given entity for deletion.
		 * Param: ID of the entity.
		 */
		template<typename COMP>
		void delete_component(std::size_t id)
		{
			if(has_component<COMP>(id))
				components_to_be_removed_.push_back(std::make_pair(id, COMP::type));
			// No need to do anything when the component is non-existent, since that is the
			// state the caller wants.
		}

		/**
		 * Brief: Allows to enqueue a component for deletion based on it's ID.
		 * Param: ID of the entity.
		 * Param: ID of the component.
		 */
		void delete_component(std::size_t, int);

		/**
		 * Brief: Deletes a component.
		 * Param: ID of the entity.
		 * Param: ID of the component.
		 */
		void delete_component_now(std::size_t, int);

		/**
		 * Brief: Initializes the graphics component of a manually created entity
		 *        by loading it's model into an Ogre::Entity and bounding it to a
		 *        scene node.
		 * Param: ID of the entity.
		 */
		void init_graphics_component(std::size_t);
	private:
		/**
		 * Brief: Loads a component from a Lua script.
		 * Param: ID of the entity.
		 * Param: Name of the table containing the component.
		 */
		template<typename COMP>
		void load_component(std::size_t id, const std::string& table_name);

		/**
		 * Contains bitsets describing component availability.
		 */
		std::map<std::size_t, std::bitset<Component::count>> entities_;

		/**
		 * Used to mark components or entire entities for removal.
		 */
		std::vector<std::size_t> to_be_destroyed_;
		std::vector<std::pair<std::size_t, int>> components_to_be_removed_;

		/**
		 * Contain components specified by the entity ID.
		 */
		std::map<std::size_t, PhysicsComponent> physics_;
		std::map<std::size_t, HealthComponent> health_;
		std::map<std::size_t, AIComponent> ai_;
		std::map<std::size_t, GraphicsComponent> graphics_;
		std::map<std::size_t, MovementComponent> movement_;
		std::map<std::size_t, CombatComponent> combat_;
		std::map<std::size_t, EventComponent> event_;
		std::map<std::size_t, InputComponent> input_;
		std::map<std::size_t, TimeComponent> time_;
		std::map<std::size_t, ManaComponent> mana_;
		std::map<std::size_t, SpellComponent> spell_;
		std::map<std::size_t, ProductionComponent> production_;
		std::map<std::size_t, GridNodeComponent> grid_node_;
		std::map<std::size_t, GridLineComponent> grid_line_;
		std::map<std::size_t, PathfindingComponent> pathfinding_;

		/**
		 * Reference to the game's scene manager used to create nodes and entities.
		 */
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

template<>
inline std::map<std::size_t, InputComponent>& EntitySystem::get_component_container<InputComponent>()
{
	return input_;
}

template<>
inline std::map<std::size_t, TimeComponent>& EntitySystem::get_component_container<TimeComponent>()
{
	return time_;
}

template<>
inline std::map<std::size_t, ManaComponent>& EntitySystem::get_component_container<ManaComponent>()
{
	return mana_;
}

template<>
inline std::map<std::size_t, SpellComponent>& EntitySystem::get_component_container<SpellComponent>()
{
	return spell_;
}

template<>
inline std::map<std::size_t, ProductionComponent>& EntitySystem::get_component_container<ProductionComponent>()
{
	return production_;
}

template<>
inline std::map<std::size_t, GridNodeComponent>& EntitySystem::get_component_container<GridNodeComponent>()
{
	return grid_node_;
}

template<>
inline std::map<std::size_t, GridLineComponent>& EntitySystem::get_component_container<GridLineComponent>()
{
	return grid_line_;
}

template<>
inline std::map<std::size_t, PathfindingComponent>& EntitySystem::get_component_container<PathfindingComponent>()
{
	return pathfinding_;
}

/**
 * Specializations of the EntitySystem::load_component method.
 * Note: Following components can only be created manually and thus don't have load_component specialization.
 *       GridNodeComponent (created by GridSystem::add_node)
 *       GridLineComponent (created by GridSystem::add_node)
 */
template<>
inline void EntitySystem::load_component<PhysicsComponent>(std::size_t id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	bool solid = script.get<bool>(table_name + ".PhysicsComponent.solid");
	physics_.emplace(std::make_pair(id, PhysicsComponent{solid}));
}

template<>
inline void EntitySystem::load_component<HealthComponent>(std::size_t id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	int max = script.get<int>(table_name + ".HealthComponent.max_hp");
	int reg = script.get<int>(table_name + ".HealthComponent.regen");
	int def = script.get<int>(table_name + ".HealthComponent.defense");
	health_.emplace(std::make_pair(id, HealthComponent(max, reg, def)));
}

template<>
inline void EntitySystem::load_component<AIComponent>(std::size_t id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	std::string blueprint = script.get<std::string>(table_name + ".AIComponent.blueprint");
	int faction = script.get<int>(table_name + ".AIComponent.faction");
	ai_.emplace(std::make_pair(id, AIComponent{blueprint, faction}));

	// Call init.
	script.call<void, int>(blueprint + ".init", id);
}

template<>
inline void EntitySystem::load_component<GraphicsComponent>(std::size_t id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	std::string mesh = script.get<std::string>(table_name + ".GraphicsComponent.mesh");
	std::string material = script.get<std::string>(table_name + ".GraphicsComponent.material");
	auto res = graphics_.emplace(std::make_pair(id, GraphicsComponent{mesh, material}));

	// Ogre init of the entity and scene node.
	auto& comp = res.first->second;
	comp.node = scene_.getRootSceneNode()->createChildSceneNode();
	comp.entity = scene_.createEntity(comp.mesh);
	comp.node->attachObject(comp.entity);
	comp.entity->setQueryFlags(1);

	if(!script.get<bool>(table_name + ".GraphicsComponent.visible"))
	{
		comp.visible = false;
		comp.node->setVisible(false);
	}
}

template<>
inline void EntitySystem::load_component<MovementComponent>(std::size_t id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	float speed = script.get<float>(table_name + ".MovementComponent.speed_modifier");
	movement_.emplace(std::make_pair(id, MovementComponent{speed}));
}

template<>
inline void EntitySystem::load_component<CombatComponent>(std::size_t id, const std::string& table_name)
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
inline void EntitySystem::load_component<EventComponent>(std::size_t id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::get_singleton();
	event_.emplace(std::make_pair(id, EventComponent{}));
}

template<>
inline void EntitySystem::load_component<InputComponent>(std::size_t id, const std::string& table_name)
{
	std::string handler = lpp::Script::get_singleton().get<std::string>(table_name + "InputComponent.input_handler");
	input_.emplace(std::make_pair(id, InputComponent{handler}));
}

template<>
inline void EntitySystem::load_component<PathfindingComponent>(std::size_t id, const std::string& table_name)
{
	std::string blueprint = lpp::Script::get_singleton().get<std::string>(table_name + "PathfindingComponent.blueprint");
	pathfinding_.emplace(std::make_pair(id, PathfindingComponent{blueprint}));
}