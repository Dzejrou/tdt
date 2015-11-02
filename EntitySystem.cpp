#include "EntitySystem.hpp"

/**
 * Brief: Macro that serves as a simpler way to use the loaders_ array when calling it's members.
 * Param: Type of the component to be loaded.
 * Param: ID of the entity that loads the component.
 * Param: Name of the table that contains the component data.
 */
#define LOAD_COMPONENT(TYPE, ID, TABLE) (((this)->*loaders_[TYPE])(ID, TABLE))

/**
 * Brief: Macro that serves as a simpler way to use the adders_ array when calling it's members.
 * Param: Type of the component to be added.
 * Param: ID of the entity that gets the new component.
 */
#define ADD_COMPONENT(TYPE, ID) (((this)->*adders_[TYPE])(ID))

/**
 * Brief: Macro that serves as a simpler way to use the deleters_ array when calling it's members.
 * Param: Type of the component to be added.
 * Param: ID of the entity whose component has to be deleted.
 */
#define DELETE_COMPONENT(TYPE, ID) (((this)->*deleters_[TYPE])(ID))

/**
 * Brief: Macro that serves as a simpler way to use the immediate_deleters_ array when calling it's members.
 * Param: Type of the component to be added.
 * Param: ID of the entity whose component has to be deleted.
 */
#define DELETE_COMPONENT_NOW(TYPE, ID) (((this)->*immediate_deleters_[TYPE])(ID))

EntitySystem::EntitySystem(Ogre::SceneManager& mgr)
	: scene_{mgr}, entities_{}, to_be_destroyed_{},
	  components_to_be_removed_{}, entity_register_{}
{
	init_function_arrays();
}

void EntitySystem::update(Ogre::Real)
{
	cleanup();
}

std::size_t EntitySystem::get_new_id()
{
	if(curr_id_ < Component::NO_ENTITY)
		return curr_id_++;
	else
	{ // Find first empty ID.
		std::size_t id{0};
		for(auto it = entities_.begin(); it != entities_.end(); ++it)
		{
			if(it->first != id) // First unused id.
				break;
			else
				++id;
		}
		return id;
	}
}

void EntitySystem::cleanup()
{
	// Remove components.
	for(auto& ent : components_to_be_removed_)
	{
		auto it = entities_.find(ent.first);
		if(it != entities_.end())
		{
			it->second.set(ent.second, false);
			if(!it->second.any()) // No components remaining -> destroy it.
				to_be_destroyed_.push_back(ent.first);
		}
		delete_component_now(ent.first, ent.second);
	}
	components_to_be_removed_.clear();

	/**
	 * Remove entire entities.
	 * NOTE: Creating a new vector and swaping it with the to_be_destroyed_ vector,
	 *       because when a TaskHandlerComponent is deleted, new entities (the tasks)
	 *       are added which might result in iterator invalidation.
	 */
	std::vector<std::size_t> tmp_to_be_destroyed_{};
	tmp_to_be_destroyed_.swap(to_be_destroyed_);
	for(auto id : tmp_to_be_destroyed_)
	{
		if(id == Component::NO_ENTITY)
			continue;

		auto entity = entities_.find(id);
		if(entity == entities_.end())
			continue;

		for(std::size_t i = 0; i < entity->second.size(); ++i)
		{
			if(entity->second.test(i))
				delete_component_now(id, i);
		}
		entities_.erase(id);
	}
}

std::size_t EntitySystem::create_entity(std::string table_name)
{
	std::size_t id = get_new_id();
	entities_.emplace(std::make_pair(id, std::bitset<Component::count>{}));

	if(table_name == "") // Allows to create empty entities that are setup manually.
		return id;
	else
		register_entity(table_name);

	auto& bits = entities_.find(id)->second;

	lpp::Script& script = lpp::Script::get_singleton();
	std::vector<int> comps = script.get_vector<int>(table_name + ".components");

	for(auto component_type : comps)
	{
		if(component_type < 0 || component_type >= (int)bits.size())
			continue; // Maybe notify in the console? Make the console a singleton?

		bits.set(component_type); // Duplicate components will just overwrite, no need for error checking.
		if(component_type >= 0 && component_type < Component::count && loaders_[component_type])
			LOAD_COMPONENT(component_type, id, table_name);
	}

	return id;
}

void EntitySystem::destroy_entity(std::size_t id)
{
	to_be_destroyed_.push_back(id);
}

const std::map<std::size_t, std::bitset<Component::count>>& EntitySystem::get_component_list() const
{
	return entities_;
}

void EntitySystem::add_component(std::size_t ent_id, int comp_id)
{
	if(comp_id >= 0 && comp_id < Component::count && adders_[comp_id])
		ADD_COMPONENT(comp_id, ent_id);
}

void EntitySystem::delete_component(std::size_t ent_id, int comp_id)
{
	if(comp_id >= 0 && comp_id < Component::count && deleters_[comp_id])
		DELETE_COMPONENT(comp_id, ent_id);
}

void EntitySystem::delete_component_now(std::size_t ent_id, int comp_id)
{
	if(comp_id >= 0 && comp_id < Component::count && immediate_deleters_[comp_id])
		DELETE_COMPONENT_NOW(comp_id, ent_id);
}

void EntitySystem::register_entity(const std::string& table_name)
{
	entity_register_.emplace(table_name);
}

std::set<std::string>& EntitySystem::get_registered_entities()
{
	return entity_register_;
}

bool EntitySystem::exists(std::size_t id) const
{
	return entities_.find(id) != entities_.end();
}

void EntitySystem::init_function_arrays()
{
	loaders_[PhysicsComponent::type] = &EntitySystem::load_component<PhysicsComponent>;
	loaders_[HealthComponent::type] = &EntitySystem::load_component<HealthComponent>;
	loaders_[AIComponent::type] = &EntitySystem::load_component<AIComponent>;
	loaders_[GraphicsComponent::type] = &EntitySystem::load_component<GraphicsComponent>;
	loaders_[MovementComponent::type] = &EntitySystem::load_component<MovementComponent>;
	loaders_[CombatComponent::type] = &EntitySystem::load_component<CombatComponent>;
	loaders_[EventComponent::type] = &EntitySystem::load_component<EventComponent>;
	loaders_[InputComponent::type] = &EntitySystem::load_component<InputComponent>;
	loaders_[TimeComponent::type] = &EntitySystem::load_component<TimeComponent>;
	loaders_[ManaComponent::type] = nullptr; // TODO
	loaders_[SpellComponent::type] = nullptr; // TODO
	loaders_[ProductionComponent::type] = &EntitySystem::load_component<ProductionComponent>;
	loaders_[GridNodeComponent::type] = nullptr;
	loaders_[ProductComponent::type] = nullptr;
	loaders_[PathfindingComponent::type] = &EntitySystem::load_component<PathfindingComponent>;
	loaders_[TaskComponent::type] = nullptr;
	loaders_[TaskHandlerComponent::type] = &EntitySystem::load_component<TaskHandlerComponent>;
	loaders_[StructureComponent::type] = &EntitySystem::load_component<StructureComponent>;
	loaders_[HomingComponent::type] = &EntitySystem::load_component<HomingComponent>;
	loaders_[EventHandlerComponent::type] = &EntitySystem::load_component<EventHandlerComponent>;
	loaders_[DestructorComponent::type] = &EntitySystem::load_component<DestructorComponent>;
	loaders_[GoldComponent::type] = &EntitySystem::load_component<GoldComponent>;
	loaders_[FactionComponent::type] = &EntitySystem::load_component<FactionComponent>;

	adders_[PhysicsComponent::type] = &EntitySystem::add_component<PhysicsComponent>;
	adders_[HealthComponent::type] = &EntitySystem::add_component<HealthComponent>;
	adders_[AIComponent::type] = &EntitySystem::add_component<AIComponent>;
	adders_[GraphicsComponent::type] = &EntitySystem::add_component<GraphicsComponent>;
	adders_[MovementComponent::type] = &EntitySystem::add_component<MovementComponent>;
	adders_[CombatComponent::type] = &EntitySystem::add_component<CombatComponent>;
	adders_[EventComponent::type] = &EntitySystem::add_component<EventComponent>;
	adders_[InputComponent::type] = &EntitySystem::add_component<InputComponent>;
	adders_[TimeComponent::type] = &EntitySystem::add_component<TimeComponent>;
	adders_[ManaComponent::type] = nullptr; // TODO
	adders_[SpellComponent::type] = nullptr; // TODO
	adders_[ProductionComponent::type] = &EntitySystem::add_component<ProductionComponent>;
	adders_[GridNodeComponent::type] = &EntitySystem::add_component<GridNodeComponent>;
	adders_[ProductComponent::type] = &EntitySystem::add_component<ProductComponent>;
	adders_[PathfindingComponent::type] = &EntitySystem::add_component<PathfindingComponent>;
	adders_[TaskComponent::type] = &EntitySystem::add_component<TaskComponent>;
	adders_[TaskHandlerComponent::type] = &EntitySystem::add_component<TaskHandlerComponent>;
	adders_[StructureComponent::type] = &EntitySystem::add_component<StructureComponent>;
	adders_[HomingComponent::type] = &EntitySystem::add_component<HomingComponent>;
	adders_[EventHandlerComponent::type] = &EntitySystem::add_component<EventHandlerComponent>;
	adders_[DestructorComponent::type] = &EntitySystem::add_component<DestructorComponent>;
	adders_[GoldComponent::type] = &EntitySystem::add_component<GoldComponent>;
	adders_[FactionComponent::type] = &EntitySystem::add_component<FactionComponent>;

	deleters_[PhysicsComponent::type] = &EntitySystem::delete_component<PhysicsComponent>;
	deleters_[HealthComponent::type] = &EntitySystem::delete_component<HealthComponent>;
	deleters_[AIComponent::type] = &EntitySystem::delete_component<AIComponent>;
	deleters_[GraphicsComponent::type] = &EntitySystem::delete_component<GraphicsComponent>;
	deleters_[MovementComponent::type] = &EntitySystem::delete_component<MovementComponent>;
	deleters_[CombatComponent::type] = &EntitySystem::delete_component<CombatComponent>;
	deleters_[EventComponent::type] = &EntitySystem::delete_component<EventComponent>;
	deleters_[InputComponent::type] = &EntitySystem::delete_component<InputComponent>;
	deleters_[TimeComponent::type] = &EntitySystem::delete_component<TimeComponent>;
	deleters_[ManaComponent::type] = nullptr; // TODO
	deleters_[SpellComponent::type] = nullptr; // TODO
	deleters_[ProductionComponent::type] = &EntitySystem::delete_component<ProductionComponent>;
	deleters_[GridNodeComponent::type] = &EntitySystem::delete_component<GridNodeComponent>;
	deleters_[ProductComponent::type] = &EntitySystem::delete_component<ProductComponent>;
	deleters_[PathfindingComponent::type] = &EntitySystem::delete_component<PathfindingComponent>;
	deleters_[TaskComponent::type] = &EntitySystem::delete_component<TaskComponent>;
	deleters_[TaskHandlerComponent::type] = &EntitySystem::delete_component<TaskHandlerComponent>;
	deleters_[StructureComponent::type] = &EntitySystem::delete_component<StructureComponent>;
	deleters_[HomingComponent::type] = &EntitySystem::delete_component<HomingComponent>;
	deleters_[EventHandlerComponent::type] = &EntitySystem::delete_component<EventHandlerComponent>;
	deleters_[DestructorComponent::type] = &EntitySystem::delete_component<DestructorComponent>;
	deleters_[GoldComponent::type] = &EntitySystem::delete_component<GoldComponent>;
	deleters_[FactionComponent::type] = &EntitySystem::delete_component<FactionComponent>;

	immediate_deleters_[PhysicsComponent::type] = &EntitySystem::delete_component_now<PhysicsComponent>;
	immediate_deleters_[HealthComponent::type] = &EntitySystem::delete_component_now<HealthComponent>;
	immediate_deleters_[AIComponent::type] = &EntitySystem::delete_component_now<AIComponent>;
	immediate_deleters_[GraphicsComponent::type] = &EntitySystem::delete_component_now<GraphicsComponent>;
	immediate_deleters_[MovementComponent::type] = &EntitySystem::delete_component_now<MovementComponent>;
	immediate_deleters_[CombatComponent::type] = &EntitySystem::delete_component_now<CombatComponent>;
	immediate_deleters_[EventComponent::type] = &EntitySystem::delete_component_now<EventComponent>;
	immediate_deleters_[InputComponent::type] = &EntitySystem::delete_component_now<InputComponent>;
	immediate_deleters_[TimeComponent::type] = &EntitySystem::delete_component_now<TimeComponent>;
	immediate_deleters_[ManaComponent::type] = nullptr; // TODO
	immediate_deleters_[SpellComponent::type] = nullptr; // TODO
	immediate_deleters_[ProductionComponent::type] = &EntitySystem::delete_component_now<ProductionComponent>;
	immediate_deleters_[GridNodeComponent::type] = &EntitySystem::delete_component_now<GridNodeComponent>;
	immediate_deleters_[ProductComponent::type] = &EntitySystem::delete_component_now<ProductComponent>;
	immediate_deleters_[PathfindingComponent::type] = &EntitySystem::delete_component_now<PathfindingComponent>;
	immediate_deleters_[TaskComponent::type] = &EntitySystem::delete_component_now<TaskComponent>;
	immediate_deleters_[TaskHandlerComponent::type] = &EntitySystem::delete_component_now<TaskHandlerComponent>;
	immediate_deleters_[StructureComponent::type] = &EntitySystem::delete_component_now<StructureComponent>;
	immediate_deleters_[HomingComponent::type] = &EntitySystem::delete_component_now<HomingComponent>;
	immediate_deleters_[EventHandlerComponent::type] = &EntitySystem::delete_component_now<EventHandlerComponent>;
	immediate_deleters_[DestructorComponent::type] = &EntitySystem::delete_component_now<DestructorComponent>;
	immediate_deleters_[GoldComponent::type] = &EntitySystem::delete_component_now<GoldComponent>;
	immediate_deleters_[FactionComponent::type] = &EntitySystem::delete_component_now<FactionComponent>;
}
