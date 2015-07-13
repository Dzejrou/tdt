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
	std::vector<int> comps = lpp::Script::get_singleton().get_vector<int>(table_name + ".components");

	for(const auto& x : comps)
	{
		switch(x)
		{
			
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
