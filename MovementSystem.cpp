#include "MovementSystem.hpp"

MovementSystem::MovementSystem(EntitySystem& ents)
	: entities_{ents}
{ /* DUMMY BODY */ }

void MovementSystem::update(Ogre::Real)
{
}

bool MovementSystem::is_valid(std::size_t id)
{
	return entities_.has_components<PhysicsComponent, MovementComponent>(id);
}

bool MovementSystem::can_move_to(std::size_t, Ogre::Vector3)
{
	return false;
}

void MovementSystem::move(std::size_t id, Ogre::Vector3 dir_vector)
{
	if(is_valid(id))
	{
		auto& phys_comp = entities_.get_component<PhysicsComponent>(id);
		auto& mov_comp = entities_.get_component<MovementComponent>(id);
	}
}

Ogre::AxisAlignedBox & MovementSystem::get_bounds(std::size_t)
{
	// TODO: insert return statement here
}
