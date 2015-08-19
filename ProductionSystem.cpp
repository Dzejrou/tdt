#include "ProductionSystem.hpp"

ProductionSystem::ProductionSystem(EntitySystem& ents, GridSystem& grid)
	: entities_{ents}, grid_{grid}
{ /* DUMMY BODY */ }

void ProductionSystem::update(Ogre::Real delta)
{
	for(auto& ent : entities_.get_component_container<ProductionComponent>())
	{
		if(ent.second.curr_produced >= ent.second.max_produced)
			continue;

		if(ent.second.curr_cd < ent.second.cooldown)
			ent.second.curr_cd += delta;
		else
			spawn_entity(ent.first, ent.second.product_blueprint);
	}
}

void ProductionSystem::spawn_entity(std::size_t producer, const std::string& blueprint)
{
}
