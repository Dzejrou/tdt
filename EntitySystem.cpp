#include "EntitySystem.hpp"

EntitySystem::EntitySystem(Ogre::SceneManager& mgr)
	: scene_{mgr}, components_{}, physics_{}, health_{}, ai_{},
	  graphics_{}, movement_{}, combat_{}, event_{}
{ /* DUMMY BODY */ }

std::size_t EntitySystem::get_new_id() const
{
	std::size_t id{0};

	for(auto it = components_.begin(); it != components_.end(); ++it)
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
	auto it = components_.begin();
	while(it != components_.end())
	{
		if(!it->second.any())
			it = components_.erase(it);
		else
			++it;
	}
}

std::size_t EntitySystem::create_entity(std::string table_name)
{
	std::size_t id = get_new_id();
	components_.emplace(std::make_pair(id, std::bitset<COMP_COUNT>{}));
	auto& bits = components_.find(id)->second; // For fast access.

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
	auto& entity = components_.find(id);

	std::string blueprint = get_component<AIComponent>(id).blueprint;
	lpp::Script::get_singleton().call<void, std::size_t>(blueprint + ".finnish", id); // Calls the "destructor".

	for(std::size_t i = 0; i < entity->second.size(); ++i)
	{
		if(!entity->second.test(i))
			continue;
		else
			entity->second.set(i, false);

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
	//components_.erase(id);
}

const std::map<std::size_t, std::bitset<COMP_COUNT>>& EntitySystem::get_component_list() const
{
	return components_;
}