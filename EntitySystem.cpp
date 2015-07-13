#include "EntitySystem.hpp"

EntitySystem::EntitySystem()
{

}

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
		bits.set(x);
		switch(x)
		{
			case PhysicsComponent::type:
				bool solid = script.get<bool>(table_name + ".solid");
				physics_.emplace(std::make_pair(id, PhysicsComponent{solid}));
				break;
			case HealthComponent::type:
				int max = script.get<int>(table_name + ".max_hp");
				int reg = script.get<int>(table_name + ".regen");
				int def = script.get<int>(table_name + ".defense");
				health_.emplace(std::make_pair(id, HealthComponent{
					// Note: static cast used to avoid signed -> unsigned warning.
					static_cast<std::size_t>(max),
					static_cast<std::size_t>(reg),
					static_cast<std::size_t>(def)
				}));
				break;
			case AIComponent::type:
				break;
			case GraphicsComponent::type:
				break;
			case MovementComponent::type:
				break;
			case CombatComponent::type:
				break;
			case EventComponent::type:
				break;
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
