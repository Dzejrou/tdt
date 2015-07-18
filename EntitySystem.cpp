#include "EntitySystem.hpp"

EntitySystem::EntitySystem(Ogre::SceneManager& mgr)
	: scene_{mgr}, entities_{}, physics_{}, health_{}, ai_{},
	  graphics_{}, movement_{}, combat_{}, event_{}, to_be_destroyed_{},
	  components_to_be_removed_{}
{ /* DUMMY BODY */ }

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
		entities_.find(ent.first)->second.set(ent.second, false);
		switch(ent.second)
		{
				case PhysicsComponent::type:
				{
					auto& phys_comp = get_component<PhysicsComponent>(ent.first);
					if(phys_comp.node && phys_comp.entity)
					{
						phys_comp.node->detachObject(phys_comp.entity);
						if(phys_comp.node->numChildren() == 0)
							scene_.destroySceneNode(phys_comp.node);
						scene_.destroyEntity(phys_comp.entity);
					}
					physics_.erase(ent.first);
					break;
				}
				case HealthComponent::type:
					health_.erase(ent.first);
					break;
				case AIComponent::type:
					ai_.erase(ent.first);
					break;
				case GraphicsComponent::type:
					graphics_.erase(ent.first);
					break;
				case MovementComponent::type:
					movement_.erase(ent.first);
					break;
				case CombatComponent::type:
					combat_.erase(ent.first);
					break;
				case EventComponent::type:
					event_.erase(ent.first);
					break;
			
			}
		if(!entities_.find(ent.first)->second.any()) // No components remaining -> destroy it.
			to_be_destroyed_.push_back(ent.first);
	}
	components_to_be_removed_.clear();

	// Remove entire entities.
	for(auto id : to_be_destroyed_)
	{
		auto& entity = entities_.find(id);

		for(std::size_t i = 0; i < entity->second.size(); ++i)
		{
			if(!entity->second.test(i))
				continue;

			switch(i)
			{ // Remove the entity from all component containers it's in.
				case PhysicsComponent::type:
				{
					auto& phys_comp = get_component<PhysicsComponent>(id);
					if(phys_comp.node && phys_comp.entity)
					{
						phys_comp.node->detachObject(phys_comp.entity);
						if(phys_comp.node->numChildren() == 0)
							scene_.destroySceneNode(phys_comp.node);
						scene_.destroyEntity(phys_comp.entity);
					}
					physics_.erase(id);
					break;
				}
				case HealthComponent::type:
					health_.erase(id);
					break;
				case AIComponent::type:
					ai_.erase(id);
					break;
				case GraphicsComponent::type:
					graphics_.erase(id);
					break;
				case MovementComponent::type:
					movement_.erase(id);
					break;
				case CombatComponent::type:
					combat_.erase(id);
					break;
				case EventComponent::type:
					event_.erase(id);
					break;
			
			}
		}
		entities_.erase(id);
	}
	to_be_destroyed_.clear();
}

std::size_t EntitySystem::create_entity(std::string table_name)
{
	std::size_t id = get_new_id();
	entities_.emplace(std::make_pair(id, std::bitset<Component::count>{}));
	auto& bits = entities_.find(id)->second; // For fast access.

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
		}
	}

	if(has_component<PhysicsComponent>(id) && has_component<GraphicsComponent>(id))
	{ // Init node and entity.
		auto& phys_comp = get_component<PhysicsComponent>(id);
		auto& graph_comp = get_component<GraphicsComponent>(id);

		phys_comp.node = scene_.getRootSceneNode()->createChildSceneNode();
		phys_comp.node->showBoundingBox(true);
		phys_comp.entity = scene_.createEntity(graph_comp.mesh);
		//phys_comp.entity->setMaterialName(graph_comp.material); // TODO: Necessary?
		phys_comp.node->attachObject(phys_comp.entity);
	}

	return id;
}

void EntitySystem::destroy_entity(std::size_t id)
{
	std::string blueprint = get_component<AIComponent>(id).blueprint;
	lpp::Script::get_singleton().call<void, std::size_t>(blueprint + ".finnish", id); // Calls the "destructor".
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
	}
}
