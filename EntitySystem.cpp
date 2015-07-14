#include "EntitySystem.hpp"

EntitySystem::EntitySystem(Ogre::SceneManager& mgr)
	: scene_{mgr}
{ /* DUMMY BODY */ }

std::size_t EntitySystem::get_new_id() const
{
	std::size_t id{0};

	for(auto it = components_.begin(); it != components_.end(); ++it)
	{
		if(it->first != id)
			return id; // First unused index.
		else
			++id;
	}

	// This should never happen, std::size_t will contain any number of entities that are
	// possible to render and update simultaneously in the game.
	throw std::exception{"[Error][EntitySystem] No more available indexes for entities."};
}

std::size_t EntitySystem::create_entity(std::string table_name)
{
	std::size_t id = get_new_id();
	components_.emplace(std::make_pair(id, std::bitset<COMP_COUNT>{}));
	auto& bits = components_.find(id)->second; // For fast access.

	lpp::Script& script = lpp::Script::get_singleton();
	std::vector<int> comps = script.get_vector<int>(table_name + ".components");

	for(const auto& x : comps)
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
		}

		if(has_components<PhysicsComponent, GraphicsComponent>(id))
		{ // Init node and entity.
			auto& phys_comp = get_component<PhysicsComponent>(id);
			auto& graph_comp = get_component<GraphicsComponent>(id);

			phys_comp.node = scene_.getRootSceneNode()->createChildSceneNode();
			phys_comp.entity = scene_.createEntity(graph_comp.mesh);
			phys_comp.entity->setMaterialName(graph_comp.material); // TODO: Necessary?
			phys_comp.node->attachObject(phys_comp.entity);
		}
	}
}

void EntitySystem::destroy_entity(std::size_t id)
{
	// TODO:
}

const std::map<std::size_t, std::bitset<COMP_COUNT>>& EntitySystem::get_component_list() const
{
	return components_;
}
