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
}