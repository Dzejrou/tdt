#include "MovementSystem.hpp"

MovementSystem::MovementSystem(EntitySystem& ents)
	: entities_{ents}
{ /* DUMMY BODY */ }

void MovementSystem::update(Ogre::Real delta)
{
	auto& ents = entities_.get_component_list();
	for(auto it = ents.cbegin(); it != ents.cend(); ++it)
	{ // TODO: Account for delta.
		if(is_valid(it->first) && is_moving(it->first))
			move(it->first, entities_.get_component<MovementComponent>(it->first).movement_vector);
	}
}

bool MovementSystem::is_valid(std::size_t id) const
{
	return entities_.has_components<PhysicsComponent, MovementComponent>(id);
}

bool MovementSystem::is_moving(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<MovementComponent>(id).moving;
}

bool MovementSystem::is_solid(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<PhysicsComponent>(id).solid;
	else
		return false;
}

bool MovementSystem::can_move_to(std::size_t id, Ogre::Vector3 pos)
{
	if(is_valid(id) && entities_.get_component<PhysicsComponent>(id).solid)
	{
		auto& ents = entities_.get_component_list();
		auto& phys_comp = entities_.get_component<PhysicsComponent>(id);
		phys_comp.node->setPosition(pos); // Old position backed up in phys_comp.position.
		auto& bounds = get_bounds(id); // TODO: Does the box update when position changes?

		for(auto it = ents.cbegin(); it != ents.cend(); ++it)
		{
			if(is_valid(it->first) && is_solid(it->first) &&
			   bounds.intersects(get_bounds(it->first)))
			{
				phys_comp.node->setPosition(phys_comp.position);
				return false;
			}
		}

		// Reverts the change, because of possible checks without actual movement.
		phys_comp.node->setPosition(phys_comp.position);
		return true;
	}
}

bool MovementSystem::move(std::size_t id, Ogre::Vector3 dir_vector)
{
	if(is_valid(id))
	{
		auto& phys_comp = entities_.get_component<PhysicsComponent>(id);
		auto& mov_comp = entities_.get_component<MovementComponent>(id);

		auto new_pos = phys_comp.position;
		auto dir = mov_comp.movement_vector;
		dir *= mov_comp.speed_modifier; 
		new_pos += dir;

		if(can_move_to(id, new_pos))
		{
			phys_comp.position = new_pos;
			phys_comp.node->setPosition(new_pos);
		}
		else
			return false;
		return true;
	}
}

void MovementSystem::move_to(std::size_t id, Ogre::Vector3 pos)
{
	if(is_valid(id))
	{
		auto& phys_comp = entities_.get_component<PhysicsComponent>(id);
		phys_comp.position = pos;
		phys_comp.node->setPosition(pos);
	}
}

const Ogre::AxisAlignedBox& MovementSystem::get_bounds(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<PhysicsComponent>(id).entity->getBoundingBox();
	else
		throw std::exception{"[Error][MovementSystem] Trying to get bounding box of entity #"
							 + std::to_string(id) + " which does not have PhysicsComponent."};
}
