#include "EntitySystem.hpp"

EntitySystem::EntitySystem(Ogre::SceneManager& mgr)
	: scene_{mgr}, entities_{}, physics_{}, health_{}, ai_{},
	  graphics_{}, movement_{}, combat_{}, event_{}, to_be_destroyed_{},
	  components_to_be_removed_{}, entity_register_{}
{ /* DUMMY BODY */ }

void EntitySystem::update(Ogre::Real)
{
	cleanup();
}

std::size_t EntitySystem::get_new_id() const
{
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

	for(auto x : comps)
	{
		bits.set(x); // Duplicate components will just overwrite, no need for error checking.
		switch(x)
		{
			case PhysicsComponent::type:
				load_component<PhysicsComponent>(id, table_name);
				break;
			case HealthComponent::type:
				load_component<HealthComponent>(id, table_name);
				break;
			case AIComponent::type:
				load_component<AIComponent>(id, table_name);
				break;
			case GraphicsComponent::type:
				load_component<GraphicsComponent>(id, table_name);
				break;
			case MovementComponent::type:
				load_component<MovementComponent>(id, table_name);
				break;
			case CombatComponent::type:
				load_component<CombatComponent>(id, table_name);
				break;
			case EventComponent::type:
				load_component<EventComponent>(id, table_name);
				break;
			case InputComponent::type:
				load_component<InputComponent>(id, table_name);
				break;
			case TimeComponent::type:
				load_component<TimeComponent>(id, table_name);
				break;
			case ManaComponent::type:
			case SpellComponent::type:
				break; // TODO: Create these components and their respective system.
			case ProductionComponent::type:
				load_component<ProductionComponent>(id, table_name);
				break;
			case GridNodeComponent::type:
				// Cannot be loaded automatically, will be handled by GridSystem.
				break;
			case ProductComponent::type:
				// Nothing to load, the production is assigned during runtime.
				break;
			case PathfindingComponent::type:
				load_component<PathfindingComponent>(id, table_name);
				break;
			case TaskComponent::type:
				// Cannot be loaded automatically, will be handled by TaskSystem.
				break;
			case TaskHandlerComponent::type:
				load_component<TaskHandlerComponent>(id, table_name);
				break;
			case StructureComponent::type:
				load_component<StructureComponent>(id, table_name);
				break;
			case HomingComponent::type:
				load_component<HomingComponent>(id, table_name);
				break;
			case EventHandlerComponent::type:
				load_component<EventHandlerComponent>(id, table_name);
				break;
			case DestructorComponent::type:
				load_component<DestructorComponent>(id, table_name);
				break;
			case GoldComponent::type:
				load_component<GoldComponent>(id, table_name);
				break;
		}
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
	switch(comp_id)
	{
		case PhysicsComponent::type:
			add_component<PhysicsComponent>(ent_id);
			break;
		case HealthComponent::type:
			add_component<HealthComponent>(ent_id);
			break;
		case AIComponent::type:
			add_component<AIComponent>(ent_id);
			break;
		case GraphicsComponent::type:
			add_component<GraphicsComponent>(ent_id);
			break;
		case MovementComponent::type:
			add_component<MovementComponent>(ent_id);
			break;
		case CombatComponent::type:
			add_component<CombatComponent>(ent_id);
			break;
		case EventComponent::type:
			add_component<EventComponent>(ent_id);
			break;
		case InputComponent::type:
			add_component<InputComponent>(ent_id);
			break;
		case TimeComponent::type:
			add_component<TimeComponent>(ent_id);
			break;
		case ManaComponent::type:
			add_component<ManaComponent>(ent_id);
			break;
		case SpellComponent::type:
			add_component<SpellComponent>(ent_id);
			break;
		case ProductionComponent::type:
			add_component<ProductionComponent>(ent_id);
			break;
		case GridNodeComponent::type:
			add_component<GridNodeComponent>(ent_id);
			break;
		case ProductComponent::type:
			add_component<ProductComponent>(ent_id);
			break;
		case PathfindingComponent::type:
			add_component<PathfindingComponent>(ent_id);
			break;
		case TaskComponent::type:
			add_component<TaskComponent>(ent_id);
			break;
		case TaskHandlerComponent::type:
			add_component<TaskHandlerComponent>(ent_id);
			break;
		case StructureComponent::type:
			add_component<StructureComponent>(ent_id);
			break;
		case HomingComponent::type:
			add_component<HomingComponent>(ent_id);
			break;
		case EventHandlerComponent::type:
			add_component<EventHandlerComponent>(ent_id);
			break;
		case DestructorComponent::type:
			add_component<DestructorComponent>(ent_id);
			break;
		case GoldComponent::type:
			add_component<GoldComponent>(ent_id);
			break;
	}
}

void EntitySystem::delete_component(std::size_t ent_id, int comp_id)
{
	switch(comp_id)
	{
		case PhysicsComponent::type:
			delete_component<PhysicsComponent>(ent_id);
			break;
		case HealthComponent::type:
			delete_component<HealthComponent>(ent_id);
			break;
		case AIComponent::type:
			delete_component<AIComponent>(ent_id);
			break;
		case GraphicsComponent::type:
			delete_component<GraphicsComponent>(ent_id);
			break;
		case MovementComponent::type:
			delete_component<MovementComponent>(ent_id);
			break;
		case CombatComponent::type:
			delete_component<CombatComponent>(ent_id);
			break;
		case EventComponent::type:
			delete_component<EventComponent>(ent_id);
			break;
		case InputComponent::type:
			delete_component<InputComponent>(ent_id);
			break;
		case TimeComponent::type:
			delete_component<TimeComponent>(ent_id);
			break;
		case ManaComponent::type:
			delete_component<ManaComponent>(ent_id);
			break;
		case SpellComponent::type:
			delete_component<SpellComponent>(ent_id);
			break;
		case ProductionComponent::type:
			delete_component<ProductionComponent>(ent_id);
			break;
		case GridNodeComponent::type:
			delete_component<GridNodeComponent>(ent_id);
			break;
		case ProductComponent::type:
			delete_component<ProductComponent>(ent_id);
			break;
		case PathfindingComponent::type:
			delete_component<PathfindingComponent>(ent_id);
			break;
		case TaskComponent::type:
			delete_component<TaskComponent>(ent_id);
			break;
		case TaskHandlerComponent::type:
			delete_component<TaskHandlerComponent>(ent_id);
			break;
		case StructureComponent::type:
			delete_component<StructureComponent>(ent_id);
			break;
		case HomingComponent::type:
			delete_component<HomingComponent>(ent_id);
			break;
		case EventHandlerComponent::type:
			delete_component<EventHandlerComponent>(ent_id);
			break;
		case DestructorComponent::type:
			delete_component<DestructorComponent>(ent_id);
			break;
		case GoldComponent::type:
			delete_component<GoldComponent>(ent_id);
			break;
	}
}

void EntitySystem::delete_component_now(std::size_t ent_id, int comp_id)
{
	auto ent = entities_.find(ent_id);
	if(ent != entities_.end())
		ent->second.set(comp_id, false);

	switch(comp_id)
	{
		case PhysicsComponent::type:
			physics_.erase(ent_id);
			break;
		case HealthComponent::type:
			health_.erase(ent_id);
			break;
		case AIComponent::type:
			ai_.erase(ent_id);
			break;
		case GraphicsComponent::type:
		{
			auto graph_comp = get_component<GraphicsComponent>(ent_id);
			if(graph_comp && graph_comp->node && graph_comp->entity)
			{
				graph_comp->node->detachObject(graph_comp->entity);
				scene_.destroyEntity(graph_comp->entity);
				if(graph_comp->node->numChildren() != 0)
					graph_comp->node->removeAndDestroyAllChildren();
				scene_.destroySceneNode(graph_comp->node);
			}
			graphics_.erase(ent_id);
			break;
		}
		case MovementComponent::type:
			movement_.erase(ent_id);
			break;
		case CombatComponent::type:
			combat_.erase(ent_id);
			break;
		case EventComponent::type:
			event_.erase(ent_id);
			break;
		case InputComponent::type:
			input_.erase(ent_id);
			break;
		case TimeComponent::type:
			time_.erase(ent_id);
			break;
		case ManaComponent::type:
		case SpellComponent::type:
			break; // TODO: Finnish remaining components.
		case ProductionComponent::type:
			production_.erase(ent_id);
		case GridNodeComponent::type:
			grid_node_.erase(ent_id);
			break;
		case ProductComponent::type:
			product_.erase(ent_id);
			break;
		case PathfindingComponent::type:
			pathfinding_.erase(ent_id);
			break;
		case TaskComponent::type:
			task_.erase(ent_id);
			break;
		case TaskHandlerComponent::type:
		{
			auto comp = get_component<TaskHandlerComponent>(ent_id);
			if(comp)
			{ // Destroy all assigned tasks.
				if(comp->curr_task != Component::NO_ENTITY)
					to_be_destroyed_.push_back(comp->curr_task);
				for(auto task : comp->task_queue)
					to_be_destroyed_.push_back(task);
			}

			task_handler_.erase(ent_id);
			break;
		}
		case StructureComponent::type:
		{
			auto comp = get_component<StructureComponent>(ent_id);
			if(comp)
			{ // Free all obstructed nodes.
				for(auto& residence : comp->residences)
				{
					auto node = get_component<GridNodeComponent>(residence);

					/**
					 * TODO: The Lua call is a workaround, change systems to singletons?
					 */
					if(node && node->resident == ent_id)
						lpp::Script::get_singleton().call<void, std::size_t, bool>("game.set_free", residence, true);
				}
			}
			structure_.erase(ent_id);
			break;
		}
		case HomingComponent::type:
			homing_.erase(ent_id);
			break;
		case EventHandlerComponent::type:
			event_handler_.erase(ent_id);
			break;
		case DestructorComponent::type:
			destructor_.erase(ent_id);
			break;
		case GoldComponent::type:
			gold_.erase(ent_id);
			break;
	}
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
