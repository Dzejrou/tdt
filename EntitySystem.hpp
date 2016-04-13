#pragma once

#include <Ogre.h>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <array>
#include "System.hpp"
#include "Components.hpp"
#include "lppscript/LppScript.hpp"
#include "Helpers.hpp"
#include "Util.hpp"
#include "Player.hpp"
#include "Typedefs.hpp"

/**
 * The EntitySystem class handles everything related to entities, like addition and removal of components,
 * testing if an entity has a component or retrieval of components belonging to particular entities.
 */
class EntitySystem : public System
{
	friend class util::EntityDestroyer;
	typedef void (EntitySystem::*LoaderFuncPtr)(tdt::uint, const std::string&);
	typedef void (EntitySystem::*AdderFuncPtr)(tdt::uint);
	typedef void (EntitySystem::*DeleterFuncPtr)(tdt::uint);
	typedef void (EntitySystem::*ImmediateDeleterFuncPtr)(tdt::uint);
	public:
		/**
		 * Brief: Constructor.
		 * Param: Reference to the game's scene manager used to create nodes and entities.
		 */
		EntitySystem(Ogre::SceneManager&);

		/**
		 * Brief: Destructor.
		 */
		~EntitySystem() = default;

		/**
		 * Brief: Checks for entities with no components and if any are found, deletes
		 *        them.
		 * Param: Time since the last frame.
		 */
		void update(tdt::real) override;

		/**
		 * Brief: Returns first available entity id.
		 */
		tdt::uint get_new_id();

		/**
		 * Brief: Removes all entities that have no components and individual components marked
		 *        for deletion from their entities (this is used so that the Lua code does not 
		 *        delete an entity/a component from a container while C++ iterates over it).
		 */
		void cleanup();

		/**
		 * Brief: Creates a new entity from a blueprint.
		 * Param: Name of the Lua table containing the entity blueprint.
		 * Param: Optional position of the entity.
		 */
		tdt::uint create_entity(const std::string& = "", const Ogre::Vector3& = Ogre::Vector3{0.f, 0.f, 0.f});

		/**
		 * Breif: Returns const reference to the component list, so that it can
		 *        be used to iterate over all entities.
		 */
		const std::map<tdt::uint, std::bitset<Component::count>>& get_component_list() const;
		
		/**
		 * Brief: Tests whether a given entity has a component specialized by the
		 *	      template argument.
		 * Param: ID of the entity being checked.
		 * Note: VS2015RC does not let me use variadic templates with recursion to check multiple
		 *       components for some reason, investigate!
		 */
		template<typename COMP>
		bool has_component(tdt::uint id)
		{
			return get_component_container<COMP>().find(id) !=
				   get_component_container<COMP>().end();
		}

		/**
		 * Brief: Tests whether a given entity has a component of a given type (used from Lua as
		 *        it cannot use templates).
		 * Param: ID of the entity.
		 * Param: Type of the component.
		 */
		bool has_component(tdt::uint, tdt::uint) const;

		/**
		 * Brief: Returns a bool-component pointer pair, in which the first bool member determines if the
		 *        component was found and the second is a pointer to the component.
		 * Param: ID of the entity whose component we ask for.
		 */
		template<typename COMP>
		COMP* get_component(tdt::uint id)
		{
			auto it = get_component_container<COMP>().find(id);
			if(it != get_component_container<COMP>().end())
				return &it->second;
			else
				return nullptr;
		}

		/**
		 * Brief: Changes a component (type specified by template argument) of and entity or assigns a new
		 *		  component it that entity didn't have it.
		 * Param: ID of the entity.
		 * Param: Component to be assigned.
		 */
		template<typename COMP>
		void set_component(tdt::uint id, COMP comp)
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
		std::map<tdt::uint, COMP>& get_component_container();

		/**
		 * Brief: Adds a components to the given enetity using it's default constructor (all values have
		 *        to be set afterwards).
		 * Param: ID of the entity.
		 */
		template<typename COMP>
		void add_component(tdt::uint id)
		{
			auto it = entities_.find(id);
			if(it != entities_.end() && !it->second.test(COMP::type))
			{
				it->second.set(COMP::type, true);
				get_component_container<COMP>().emplace(id, COMP{});
			}
		}

		/**
		 * Brief: Allows to add a component based on it's ID.
		 * Param: ID of the entity.
		 * Param: ID of the component.
		 */
		void add_component(tdt::uint, int);

		/**
		 * Brief: Marks a component (specified by template argument) for given entity for deletion.
		 * Param: ID of the entity.
		 */
		template<typename COMP>
		void delete_component(tdt::uint id)
		{
				components_to_be_removed_.push_back(std::make_pair(id, COMP::type));
		}

		/**
		 * Brief: Allows to enqueue a component for deletion based on it's ID.
		 * Param: ID of the entity.
		 * Param: ID of the component.
		 */
		void delete_component(tdt::uint, int);

		/**
		 * Brief: Registers an entity that has been loaded from a Lua script.
		 *        (If it has been registered previously, the register ignores it.)
		 * Param: Name of the table containing the info about the entity.
		 */
		void register_entity(const std::string&);

		/**
		 * Brief: Returns a reference to the set containing all entity tables registered
		 *        during the game's runtime.
		 */
		std::set<std::string>& get_registered_entities();

		/**
		 * Brief: Checks if a given entity exists and returns true if it does, false otherwise.
		 * Param: ID of the entity.
		 */
		bool exists(tdt::uint) const;

		/**
		 * Brief: Returns a reference to the scene manager all entities of this system are
		 *        attached to (if they have a graphics component).
		 */
		Ogre::SceneManager& get_scene_manager() { return scene_; }

		/**
		 * Brief: Deletes all entities int the game, used before loading a new game.
		 */
		void delete_entities();

		/**
		 * Used in helpers when no component exists and we still need to return
		 * the blueprint name (in this case the ERROR blueprint) by reference.
		 */
		std::string NO_BLUEPRINT{"ERROR"};

		/**
		 * Used in when translating the faction enum to a string in the FactionHelper.
		 */
		std::array<std::string, 3> FACTION_NAME{"FRIENDLY", "ENEMY", "NEUTRAL"};

	private:
		/**
		 * Brief: Loads a component from a Lua script.
		 * Param: ID of the entity.
		 * Param: Name of the table containing the component.
		 */
		template<typename COMP>
		void load_component(tdt::uint id, const std::string& table_name);

		/**
		 * Brief: Removes an entity from the system, thus killing/destroying it.
		 * Param: ID of the entity.
		 */
		void destroy_entity(tdt::uint);

		/**
		 * Brief: Deletes a component.
		 * Param: ID of the entity.
		 */
		template<typename COMP>
		void delete_component_now(tdt::uint id)
		{
			auto ent = entities_.find(id);
			if(ent != entities_.end())
				ent->second.set(COMP::type, false);
			clean_up_component<COMP>(id);
			get_component_container<COMP>().erase(id);
		}

		/**
		 * Brief: Deletes a component.
		 * Param: ID of the entity.
		 * Param: ID of the component.
		 */
		void delete_component_now(tdt::uint, int);

		/**
		 * Brief: Initializes all arrays holding pointers to the component
		 *        manipulating methods.
		 */
		void init_function_arrays();

		/**
		 * Brief: Deletes all necessary data when destroying a component (like Ogre
		 *        related objects, other entities, tasks etc.).
		 * Param: ID of the entity.
		 */
		template<typename COMP>
		void clean_up_component(tdt::uint)
		{ /* DUMMY BODY */ }

		/**
		 * Contains bitsets describing component availability.
		 */
		std::map<tdt::uint, std::bitset<Component::count>> entities_;

		/**
		 * Used to mark components or entire entities for removal.
		 */
		std::vector<tdt::uint> to_be_destroyed_;
		std::vector<std::pair<tdt::uint, int>> components_to_be_removed_;

		/**
		 * Contain components specified by the entity ID.
		 * Initialized here to avoid a long initializing list in the constructor.
		 */
		std::map<tdt::uint, PhysicsComponent> physics_{};
		std::map<tdt::uint, HealthComponent> health_{};
		std::map<tdt::uint, AIComponent> ai_{};
		std::map<tdt::uint, GraphicsComponent> graphics_{};
		std::map<tdt::uint, MovementComponent> movement_{};
		std::map<tdt::uint, CombatComponent> combat_{};
		std::map<tdt::uint, EventComponent> event_{};
		std::map<tdt::uint, InputComponent> input_{};
		std::map<tdt::uint, TimeComponent> time_{};
		std::map<tdt::uint, ManaComponent> mana_{};
		std::map<tdt::uint, SpellComponent> spell_{};
		std::map<tdt::uint, ProductionComponent> production_{};
		std::map<tdt::uint, GridNodeComponent> grid_node_{};
		std::map<tdt::uint, ProductComponent> product_{};
		std::map<tdt::uint, PathfindingComponent> pathfinding_{};
		std::map<tdt::uint, TaskComponent> task_{};
		std::map<tdt::uint, TaskHandlerComponent> task_handler_{};
		std::map<tdt::uint, StructureComponent> structure_{};
		std::map<tdt::uint, HomingComponent> homing_{};
		std::map<tdt::uint, EventHandlerComponent> event_handler_{};
		std::map<tdt::uint, DestructorComponent> destructor_{};
		std::map<tdt::uint, GoldComponent> gold_{};
		std::map<tdt::uint, FactionComponent> faction_{};
		std::map<tdt::uint, PriceComponent> price_{};
		std::map<tdt::uint, AlignComponent> align_{};
		std::map<tdt::uint, MineComponent> mine_{};
		std::map<tdt::uint, ManaCrystalComponent> mana_crystal_{};
		std::map<tdt::uint, OnHitComponent> on_hit_{};
		std::map<tdt::uint, ConstructorComponent> constructor_{};
		std::map<tdt::uint, TriggerComponent> trigger_{};
		std::map<tdt::uint, UpgradeComponent> upgrade_{};
		std::map<tdt::uint, NotificationComponent> notification_{};
		std::map<tdt::uint, ExplosionComponent> explosion_{};
		std::map<tdt::uint, LimitedLifeSpanComponent> limited_life_span_{};
		std::map<tdt::uint, NameComponent> name_{};
		std::map<tdt::uint, ExperienceValueComponent> exp_value_{};
		std::map<tdt::uint, LightComponent> light_{};
		std::map<tdt::uint, CommandComponent> command_{};
		std::map<tdt::uint, CounterComponent> counter_{};
		std::map<tdt::uint, PortalComponent> portal_{};

		/**
		 * Reference to the game's scene manager used to create nodes and entities.
		 */
		Ogre::SceneManager& scene_;

		/**
		 * Contains the names of all loaded entity tables.
		 */
		std::set<std::string> entity_register_;

		/**
		 * These arrays contain pointers to the component managment methods for easier
		 * use when Lua interacts with C++, since Lua doesn't know anything about C++
		 * types and templates.
		 */
		std::array<LoaderFuncPtr, Component::count> loaders_{};
		std::array<AdderFuncPtr, Component::count> adders_{};
		std::array<DeleterFuncPtr, Component::count> deleters_{};
		std::array<ImmediateDeleterFuncPtr, Component::count> immediate_deleters_{};

		/**
		 * Keeps track of the highest ID given to an entity.
		 */
		tdt::uint curr_id_{};

		/**
		 * Entities that should have their constructors called on the next
		 * update (freshly created), this will allow the creator of the entity to
		 * set it's position if he could not pass that position to the create_entity
		 * function.
		 */
		std::vector<tdt::uint> constructors_to_be_called_{};
};

/**
 * Specializations of the EntitySystem::get_component_container method.
 */
template<>
inline std::map<tdt::uint, PhysicsComponent>& EntitySystem::get_component_container<PhysicsComponent>()
{
	return physics_;
}

template<>
inline std::map<tdt::uint, HealthComponent>& EntitySystem::get_component_container<HealthComponent>()
{
	return health_;
}

template<>
inline std::map<tdt::uint, AIComponent>& EntitySystem::get_component_container<AIComponent>()
{
	return ai_;
}

template<>
inline std::map<tdt::uint, GraphicsComponent>& EntitySystem::get_component_container<GraphicsComponent>()
{
	return graphics_;
}

template<>
inline std::map<tdt::uint, MovementComponent>& EntitySystem::get_component_container<MovementComponent>()
{
	return movement_;
}

template<>
inline std::map<tdt::uint, CombatComponent>& EntitySystem::get_component_container<CombatComponent>()
{
	return combat_;
}

template<>
inline std::map<tdt::uint, EventComponent>& EntitySystem::get_component_container<EventComponent>()
{
	return event_;
}

template<>
inline std::map<tdt::uint, InputComponent>& EntitySystem::get_component_container<InputComponent>()
{
	return input_;
}

template<>
inline std::map<tdt::uint, TimeComponent>& EntitySystem::get_component_container<TimeComponent>()
{
	return time_;
}

template<>
inline std::map<tdt::uint, ManaComponent>& EntitySystem::get_component_container<ManaComponent>()
{
	return mana_;
}

template<>
inline std::map<tdt::uint, SpellComponent>& EntitySystem::get_component_container<SpellComponent>()
{
	return spell_;
}

template<>
inline std::map<tdt::uint, ProductionComponent>& EntitySystem::get_component_container<ProductionComponent>()
{
	return production_;
}

template<>
inline std::map<tdt::uint, GridNodeComponent>& EntitySystem::get_component_container<GridNodeComponent>()
{
	return grid_node_;
}

template<>
inline std::map<tdt::uint, ProductComponent>& EntitySystem::get_component_container<ProductComponent>()
{
	return product_;
}

template<>
inline std::map<tdt::uint, PathfindingComponent>& EntitySystem::get_component_container<PathfindingComponent>()
{
	return pathfinding_;
}

template<>
inline std::map<tdt::uint, TaskComponent>& EntitySystem::get_component_container<TaskComponent>()
{
	return task_;
}

template<>
inline std::map<tdt::uint, TaskHandlerComponent>& EntitySystem::get_component_container<TaskHandlerComponent>()
{
	return task_handler_;
}

template<>
inline std::map<tdt::uint, StructureComponent>& EntitySystem::get_component_container<StructureComponent>()
{
	return structure_;
}

template<>
inline std::map<tdt::uint, HomingComponent>& EntitySystem::get_component_container<HomingComponent>()
{
	return homing_;
}

template<>
inline std::map<tdt::uint, EventHandlerComponent>& EntitySystem::get_component_container<EventHandlerComponent>()
{
	return event_handler_;
}

template<>
inline std::map<tdt::uint, DestructorComponent>& EntitySystem::get_component_container<DestructorComponent>()
{
	return destructor_;
}

template<>
inline std::map<tdt::uint, GoldComponent>& EntitySystem::get_component_container<GoldComponent>()
{
	return gold_;
}

template<>
inline std::map<tdt::uint, FactionComponent>& EntitySystem::get_component_container<FactionComponent>()
{
	return faction_;
}

template<>
inline std::map<tdt::uint, PriceComponent>& EntitySystem::get_component_container<PriceComponent>()
{
	return price_;
}

template<>
inline std::map<tdt::uint, AlignComponent>& EntitySystem::get_component_container<AlignComponent>()
{
	return align_;
}

template<>
inline std::map<tdt::uint, MineComponent>& EntitySystem::get_component_container<MineComponent>()
{
	return mine_;
}

template<>
inline std::map<tdt::uint, ManaCrystalComponent>& EntitySystem::get_component_container<ManaCrystalComponent>()
{
	return mana_crystal_;
}

template<>
inline std::map<tdt::uint, OnHitComponent>& EntitySystem::get_component_container<OnHitComponent>()
{
	return on_hit_;
}

template<>
inline std::map<tdt::uint, ConstructorComponent>& EntitySystem::get_component_container<ConstructorComponent>()
{
	return constructor_;
}

template<>
inline std::map<tdt::uint, TriggerComponent>& EntitySystem::get_component_container<TriggerComponent>()
{
	return trigger_;
}

template<>
inline std::map<tdt::uint, UpgradeComponent>& EntitySystem::get_component_container<UpgradeComponent>()
{
	return upgrade_;
}

template<>
inline std::map<tdt::uint, NotificationComponent>& EntitySystem::get_component_container<NotificationComponent>()
{
	return notification_;
}

template<>
inline std::map<tdt::uint, ExplosionComponent>& EntitySystem::get_component_container<ExplosionComponent>()
{
	return explosion_;
}

template<>
inline std::map<tdt::uint, LimitedLifeSpanComponent>& EntitySystem::get_component_container<LimitedLifeSpanComponent>()
{
	return limited_life_span_;
}

template<>
inline std::map<tdt::uint, NameComponent>& EntitySystem::get_component_container<NameComponent>()
{
	return name_;
}

template<>
inline std::map<tdt::uint, ExperienceValueComponent>& EntitySystem::get_component_container<ExperienceValueComponent>()
{
	return exp_value_;
}

template<>
inline std::map<tdt::uint, LightComponent>& EntitySystem::get_component_container<LightComponent>()
{
	return light_;
}

template<>
inline std::map<tdt::uint, CommandComponent>& EntitySystem::get_component_container<CommandComponent>()
{
	return command_;
}

template<>
inline std::map<tdt::uint, CounterComponent>& EntitySystem::get_component_container<CounterComponent>()
{
	return counter_;
}

template<>
inline std::map<tdt::uint, PortalComponent>& EntitySystem::get_component_container<PortalComponent>()
{
	return portal_;
}

/**
 * Specializations of the EntitySystem::load_component method.
 * Note: Following components can only be created manually and thus don't have load_component specialization.
 *       GridNodeComponent (created by GridSystem::add_node)
 *       ProductComponent (production id is assigned during runtime)
 *       TaskComponent     (tasks are specified by their types and are added through the TaskHelper)
 */
template<>
inline void EntitySystem::load_component<PhysicsComponent>(tdt::uint id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::instance();
	bool solid = script.get<bool>(table_name + ".PhysicsComponent.solid");
	physics_.emplace(id, PhysicsComponent{solid});
}

template<>
inline void EntitySystem::load_component<HealthComponent>(tdt::uint id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::instance();
	int max = script.get<int>(table_name + ".HealthComponent.max_hp");
	int reg = script.get<int>(table_name + ".HealthComponent.regen");
	int def = script.get<int>(table_name + ".HealthComponent.defense");
	health_.emplace(id, HealthComponent(max, reg, def));
}

template<>
inline void EntitySystem::load_component<AIComponent>(tdt::uint id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::instance();
	std::string blueprint = script.get<std::string>(table_name + ".AIComponent.blueprint");
	ai_.emplace(id, AIComponent{std::move(blueprint)});
}

template<>
inline void EntitySystem::load_component<GraphicsComponent>(tdt::uint id, const std::string& table_name)
{ 
	lpp::Script& script = lpp::Script::instance();
	std::string mesh = script.get<std::string>(table_name + ".GraphicsComponent.mesh");
	std::string material = script.get<std::string>(table_name + ".GraphicsComponent.material");
	auto res = graphics_.emplace(id, GraphicsComponent{std::move(mesh), std::move(material)});

	// Ogre init of the entity and scene node.
	auto& comp = res.first->second;
	comp.node = scene_.getRootSceneNode()->createChildSceneNode("entity_" + std::to_string(id));
	comp.entity = scene_.createEntity(comp.mesh);
	comp.node->attachObject(comp.entity);
	comp.entity->setQueryFlags(1);

	if(!script.get<bool>(table_name + ".GraphicsComponent.visible"))
	{
		comp.visible = false;
		comp.node->setVisible(false);
	}

	if(script.get<bool>(table_name + ".GraphicsComponent.manual_scaling"))
	{
		comp.manual_scaling = true;
		tdt::real x, y, z;
		x = script.get<tdt::real>(table_name + ".GraphicsComponent.scale_x");
		y = script.get<tdt::real>(table_name + ".GraphicsComponent.scale_y");
		z = script.get<tdt::real>(table_name + ".GraphicsComponent.scale_z");
		comp.scale = Ogre::Vector3{x, y, z};
		comp.node->setScale(comp.scale);
	}

	if(comp.material != "NO_MAT")
		comp.entity->setMaterialName(comp.material);

	// Make the entity stand on ground.
	auto half_height = comp.entity->getWorldBoundingBox(true).getHalfSize().y;
	auto phys_comp = get_component<PhysicsComponent>(id);
	if(phys_comp)
	{
		phys_comp->half_height = half_height;
		phys_comp->position = Ogre::Vector3{phys_comp->position.x, half_height, phys_comp->position.z};
		comp.node->setPosition(phys_comp->position);
	}

	// This will allow specific querying.
	if(!script.is_nil(table_name + ".GraphicsComponent.query_flags"))
		comp.entity->setQueryFlags(script.get<int>(table_name + ".GraphicsComponent.query_flags"));

	// Attach a light if a light component was loaded before the graphics one.
	auto light = get_component<LightComponent>(id);
	if(light && light->light && comp.node)
		comp.node->attachObject(light->light); 

	comp.entity->setRenderingDistance(4000.f);
}

template<>
inline void EntitySystem::load_component<MovementComponent>(tdt::uint id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::instance();
	float speed = script.get<float>(table_name + ".MovementComponent.speed_modifier");
	movement_.emplace(id, MovementComponent{speed});
}

template<>
inline void EntitySystem::load_component<CombatComponent>(tdt::uint id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::instance();
	tdt::real range = script.get<tdt::real>(table_name + ".CombatComponent.range");
	tdt::real cd = script.get<tdt::real>(table_name + ".CombatComponent.cooldown");
	tdt::uint min = script.get<tdt::uint>(table_name + ".CombatComponent.min_dmg");
	tdt::uint max = script.get<tdt::uint>(table_name + ".CombatComponent.max_dmg");
	bool pursue = script.get<bool>(table_name + ".CombatComponent.pursue");
	int type = script.get<int>(table_name + ".CombatComponent.type");
	if(type == (int)ATTACK_TYPE::RANGED)
	{
		std::string proj = script.get<std::string>(table_name + ".CombatComponent.projectile_blueprint");
		combat_.emplace(id, CombatComponent(Component::NO_ENTITY, min, max, cd, range, type, pursue, std::move(proj)));
	}
	else
		combat_.emplace(id, CombatComponent(Component::NO_ENTITY, min, max, cd, range, type, pursue));
}

template<>
inline void EntitySystem::load_component<EventComponent>(tdt::uint id, const std::string& table_name)
{
	lpp::Script& script = lpp::Script::instance();
	EVENT_TYPE type = (EVENT_TYPE)script.get<int>(table_name + ".EventComponent.type");
	tdt::uint target = script.get<tdt::uint>(table_name + ".EventComponent.target");
	tdt::real radius = script.get<tdt::real>(table_name + ".EventComponent.radius");
	bool active = script.get<bool>(table_name + ".EventComponent.active");
	event_.emplace(id, EventComponent{type, target, radius, active});
}

template<>
inline void EntitySystem::load_component<InputComponent>(tdt::uint id, const std::string& table_name)
{
	std::string handler = lpp::Script::instance().get<std::string>(table_name + ".InputComponent.input_handler");
	input_.emplace(id, InputComponent{std::move(handler)});
}

template<>
inline void EntitySystem::load_component<TimeComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	int type = script.get<int>(table_name + ".TimeComponent.type");
	tdt::real time_limit = script.get<tdt::real>(table_name + ".TimeComponent.time_limit");
	tdt::uint target = script.get<tdt::uint>(table_name + ".TimeComponent.target");
	time_.emplace(id, TimeComponent{(TIME_EVENT)type, time_limit, target});
}

template<>
inline void EntitySystem::load_component<ManaComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	tdt::uint max = script.get<tdt::uint>(table_name + ".ManaComponent.max_mana");
	tdt::uint regen = script.get<tdt::uint>(table_name + ".ManaComponent.regen");
	mana_.emplace(id, ManaComponent{max, regen});
}

template<>
inline void EntitySystem::load_component<SpellComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	std::string blueprint = script.get<std::string>(table_name + ".SpellComponent.blueprint");
	tdt::real cooldown = script.get<tdt::real>(table_name + ".SpellComponent.cooldown");
	spell_.emplace(id, SpellComponent{std::move(blueprint), cooldown});
}

template<>
inline void EntitySystem::load_component<ProductionComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	std::string blueprint = script.get<std::string>(table_name + ".ProductionComponent.blueprint");
	tdt::uint limit = script.get<tdt::uint>(table_name + ".ProductionComponent.limit");
	tdt::real cd = script.get<tdt::real>(table_name + ".ProductionComponent.cooldown");
	production_.emplace(id, ProductionComponent{std::move(blueprint), limit, cd});

	if(!script.is_nil(table_name + ".FactionComponent") &&
	   script.get<tdt::uint>(table_name + ".FactionComponent.faction") == (tdt::uint)FACTION::FRIENDLY)
		Player::instance().add_max_unit(limit);
}

template<>
inline void EntitySystem::load_component<PathfindingComponent>(tdt::uint id, const std::string& table_name)
{
	std::string blueprint = lpp::Script::instance().get<std::string>(table_name + ".PathfindingComponent.blueprint");
	pathfinding_.emplace(id, PathfindingComponent{std::move(blueprint)});
}

template<>
inline void EntitySystem::load_component<TaskHandlerComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	std::vector<int> possible_tasks = script.get_vector<int>(table_name + ".TaskHandlerComponent.possible_tasks");
	std::string blueprint = script.get<std::string>(table_name + ".TaskHandlerComponent.blueprint");
	auto res = task_handler_.emplace(id, TaskHandlerComponent{std::move(blueprint)});

	// Init possible tasks.
	auto& tasks = res.first->second.possible_tasks;
	for(auto task_type : possible_tasks)
		tasks.set(task_type);
}

template<>
inline void EntitySystem::load_component<StructureComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	tdt::uint radius = script.get<tdt::uint>(table_name + ".StructureComponent.radius");

	bool walk_through{false};
	if(!script.is_nil(table_name + ".StructureComponent.walk_through"))
		walk_through = script.get<bool>(table_name + ".StructureComponent.walk_through");
	structure_.emplace(id, StructureComponent{radius, walk_through});
}

template<>
inline void EntitySystem::load_component<HomingComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	tdt::uint source = script.get<tdt::uint>(table_name + ".HomingComponent.source");
	tdt::uint target = script.get<tdt::uint>(table_name + ".HomingComponent.target");
	tdt::uint dmg = script.get<tdt::uint>(table_name + ".HomingComponent.damage");
	homing_.emplace(id, HomingComponent{source, target, dmg});
}

template<>
inline void EntitySystem::load_component<EventHandlerComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	std::string handler = script.get<std::string>(table_name + ".EventHandlerComponent.handler");
	auto res = event_handler_.emplace(id, EventHandlerComponent{std::move(handler)});

	if(!res.second)
		return;

	auto& comp = res.first->second;
	auto possible_events = script.get_vector<int>(table_name + ".EventHandlerComponent.possible_events");
	for(const auto& evt : possible_events)
		comp.possible_events.set(evt);
}

template<>
inline void EntitySystem::load_component<DestructorComponent>(tdt::uint id, const std::string& table_name)
{
	std::string blueprint = lpp::Script::instance().get<std::string>(table_name + ".DestructorComponent.blueprint");
	destructor_.emplace(id, DestructorComponent{blueprint});
}

template<>
inline void EntitySystem::load_component<GoldComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	tdt::uint curr = script.get<tdt::uint>(table_name + ".GoldComponent.curr");
	tdt::uint max = script.get<tdt::uint>(table_name + ".GoldComponent.max");
	gold_.emplace(id, GoldComponent{max, curr});
}

template<>
inline void EntitySystem::load_component<FactionComponent>(tdt::uint id, const std::string& table_name)
{
	FACTION fac =  (FACTION)lpp::Script::instance().get<int>(table_name + ".FactionComponent.faction");
	faction_.emplace(id, FactionComponent{fac});
}

template<>
inline void EntitySystem::load_component<PriceComponent>(tdt::uint id, const std::string& table_name)
{
	tdt::uint price = lpp::Script::instance().get<tdt::uint>(table_name + ".PriceComponent.price");
	price_.emplace(id, PriceComponent{price});
}

template<>
inline void EntitySystem::load_component<AlignComponent>(tdt::uint id, const std::string& table_name)
{
	auto res = align_.emplace(id, AlignComponent{});

	if(!res.second)
		return; // TODO: Notify.

	auto& comp = res.first->second;
	std::string state_table{};
	auto& script = lpp::Script::instance();
	for(tdt::uint i = 0; i < AlignComponent::state_count; ++i)
	{
		state_table = table_name + ".AlignComponent.state_" + std::to_string(i);
		comp.states[i].material = script.get<std::string>(state_table + ".material");
		comp.states[i].mesh = script.get<std::string>(state_table + ".mesh");;
		comp.states[i].position_offset.x = script.get<tdt::real>(state_table + ".position_offset_x");;
		comp.states[i].position_offset.y = script.get<tdt::real>(state_table + ".position_offset_y");;
		comp.states[i].position_offset.z = script.get<tdt::real>(state_table + ".position_offset_z");;
		comp.states[i].scale.x = script.get<tdt::real>(state_table + ".scale_x");;
		comp.states[i].scale.y = script.get<tdt::real>(state_table + ".scale_y");;
		comp.states[i].scale.z = script.get<tdt::real>(state_table + ".scale_z");;
	}
}

template<>
inline void EntitySystem::load_component<MineComponent>(tdt::uint id, const std::string& table_name)
{
	mine_.emplace(id, MineComponent{});
}

template<>
inline void EntitySystem::load_component<ManaCrystalComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	tdt::uint cap = script.get<tdt::uint>(table_name + ".ManaCrystalComponent.cap_increase");
	tdt::uint regen = script.get<tdt::uint>(table_name + ".ManaCrystalComponent.regen_increase");
	mana_crystal_.emplace(id, ManaCrystalComponent{cap, regen});

	Player::instance().add_max_mana(cap);
	Player::instance().add_mana_regen(regen);
}

template<>
inline void EntitySystem::load_component<OnHitComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	std::string blueprint = script.get<std::string>(table_name + ".OnHitComponent.blueprint");
	tdt::real cd = script.get<tdt::real>(table_name + ".OnHitComponent.cooldown");
	on_hit_.emplace(id, OnHitComponent{std::move(blueprint), cd});
}

template<>
inline void EntitySystem::load_component<ConstructorComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	std::string blueprint = script.get<std::string>(table_name + ".ConstructorComponent.blueprint");
	constructor_.emplace(id, ConstructorComponent{std::move(blueprint)});
}

template<>
inline void EntitySystem::load_component<TriggerComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	std::string blueprint = script.get<std::string>(table_name + ".TriggerComponent.blueprint");
	tdt::real cd = script.get<tdt::real>(table_name + ".TriggerComponent.cooldown");
	tdt::real radius = script.get<tdt::real>(table_name + ".TriggerComponent.radius");
	trigger_.emplace(id, TriggerComponent{std::move(blueprint), cd, radius});
}

template<>
inline void EntitySystem::load_component<UpgradeComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	std::string blueprint = script.get<std::string>(table_name + ".UpgradeComponent.blueprint");
	tdt::uint exp = script.get<tdt::uint>(table_name + ".UpgradeComponent.exp_needed");
	tdt::uint cap = script.get<tdt::uint>(table_name + ".UpgradeComponent.level_cap");
	upgrade_.emplace(id, UpgradeComponent{std::move(blueprint), exp, cap});
}

template<>
inline void EntitySystem::load_component<NotificationComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	tdt::real cd = script.get<tdt::real>(table_name + ".NotificationComponent.cooldown");
	notification_.emplace(id, NotificationComponent{cd});
}

template<>
inline void EntitySystem::load_component<ExplosionComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	tdt::real delta = script.get<tdt::real>(table_name + ".ExplosionComponent.delta");
	tdt::real radius = script.get<tdt::real>(table_name + ".ExplosionComponent.radius");
	explosion_.emplace(id, ExplosionComponent{delta, radius});
}

template<>
inline void EntitySystem::load_component<LimitedLifeSpanComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	tdt::real max = script.get<tdt::real>(table_name + ".LimitedLifeSpanComponent.max_time");
	limited_life_span_.emplace(id, LimitedLifeSpanComponent{max});
}

template<>
inline void EntitySystem::load_component<NameComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	std::string name = script.get<std::string>(table_name + ".NameComponent.name");
	name_.emplace(id, NameComponent{std::move(name)});
}

template<>
inline void EntitySystem::load_component<ExperienceValueComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	tdt::uint val = script.get<tdt::uint>(table_name + ".ExperienceValueComponent.value");
	exp_value_.emplace(id, ExperienceValueComponent{val});
}

template<>
inline void EntitySystem::load_component<LightComponent>(tdt::uint id, const std::string& table_name)
{
	auto res = light_.emplace(id, LightComponent{});
	
	if(res.second)
	{
		auto& comp = res.first->second;
		comp.light = scene_.createLight("entity_" + std::to_string(id) + "_light");
		comp.light->setType(Ogre::Light::LT_POINT);
		comp.light->setVisible(true);
		comp.light->setPosition(comp.light->getPosition() + Ogre::Vector3{0.f, 45.f, 0.f});
		comp.light->setDiffuseColour(1.f, .5f, 0.f);
		comp.light->setSpecularColour(1.f, 1.f, 0.f);
		comp.light->setAttenuation(3250.f, 1.f, .0014f, .000007f);

		auto graph = get_component<GraphicsComponent>(id);
		if(graph)
		{
			comp.node = graph->node;
			comp.node->attachObject(comp.light);
		}
	}
}

template<>
inline void EntitySystem::load_component<CommandComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	auto res = command_.emplace(id, CommandComponent{});

	if(res.second)
	{
		auto& comp = res.first->second;
		auto possible_commands = script.get_vector<int>(table_name + ".CommandComponent.possible_commands");
		for(const auto& command : possible_commands)
			comp.possible_commands.set(command);
	}
}

template<>
inline void EntitySystem::load_component<CounterComponent>(tdt::uint id, const std::string& table_name)
{
	auto& script = lpp::Script::instance();
	tdt::uint max = script.get<tdt::uint>(table_name + ".CounterComponent.max_value");
	counter_.emplace(id, CounterComponent{max});
}

template<>
inline void EntitySystem::load_component<PortalComponent>(tdt::uint id, const std::string& table_name)
{
	portal_.emplace(id, PortalComponent{});
}

/**
 * Specializations of the EntitySystem::clean_up_component method.
 */
template<>
inline void EntitySystem::clean_up_component<GraphicsComponent>(tdt::uint id)
{
	auto graph_comp = get_component<GraphicsComponent>(id);
	if(graph_comp && graph_comp->node && graph_comp->entity)
	{
		graph_comp->node->detachObject(graph_comp->entity);
		scene_.destroyEntity(graph_comp->entity);
		if(graph_comp->node->numChildren() != 0)
			graph_comp->node->removeAndDestroyAllChildren();
		scene_.destroySceneNode(graph_comp->node);
	}
}
template<>
inline void EntitySystem::clean_up_component<TaskHandlerComponent>(tdt::uint id)
{
	auto comp = get_component<TaskHandlerComponent>(id);
	if(comp)
	{ // Destroy all assigned tasks.
		if(comp->curr_task != Component::NO_ENTITY)
			to_be_destroyed_.push_back(comp->curr_task);
		for(auto task : comp->task_queue)
			to_be_destroyed_.push_back(task);
	}
}

template<>
inline void EntitySystem::clean_up_component<StructureComponent>(tdt::uint id)
{
	auto comp = get_component<StructureComponent>(id);
	if(comp)
	{ // Free all obstructed nodes.
		for(auto& residence : comp->residences)
		{
			auto node = get_component<GridNodeComponent>(residence);

			if(node && node->resident == id)
				GridNodeHelper::set_free(*this, residence, true);
		}
	}
}

template<>
inline void EntitySystem::clean_up_component<ProductComponent>(tdt::uint id)
{
	auto comp = get_component<ProductComponent>(id);
	if(comp)
	{
		auto producent = get_component<ProductionComponent>(comp->producer);
		if(producent)
			--producent->curr_produced;
	}

	auto fac = get_component<FactionComponent>(id);
	if(fac && fac->faction == FACTION::FRIENDLY)
		Player::instance().sub_curr_unit(1);
}

template<>
inline void EntitySystem::clean_up_component<ProductionComponent>(tdt::uint id)
{
	auto comp = get_component<ProductionComponent>(id);
	auto fac = get_component<FactionComponent>(id);
	if(comp && fac && fac->faction == FACTION::FRIENDLY)
		Player::instance().sub_max_unit(comp->max_produced);
}

template<>
inline void EntitySystem::clean_up_component<ManaCrystalComponent>(tdt::uint id)
{
	auto comp = get_component<ManaCrystalComponent>(id);
	if(comp)
	{
		Player::instance().sub_max_mana(comp->cap_increase);
		Player::instance().sub_mana_regen(comp->regen_increase);
	}
}

template<>
inline void EntitySystem::clean_up_component<LightComponent>(tdt::uint id)
{
	auto comp = get_component<LightComponent>(id);
	if(comp && comp->light)
		scene_.destroyLight(comp->light);
}