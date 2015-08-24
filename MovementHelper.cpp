#include "MovementHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

Ogre::Real MovementHelper::get_speed_modifier(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<MovementComponent>(id);
	if(comp)
		return comp->speed_modifier;
	else
		return Ogre::Real{};
}

void MovementHelper::set_speed_modifier(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<MovementComponent>(id);
	if(comp)
		comp->speed_modifier = val;
}