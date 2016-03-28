#include "MovementSystem.hpp"
#include "EntitySystem.hpp"
#include "Components.hpp"
#include "PhysicsHelper.hpp"
#include "GraphicsHelper.hpp"
#include "MovementHelper.hpp"
#include <limits>

MovementSystem::MovementSystem(EntitySystem& ents)
	: entities_{ents}, last_delta_{}
{ /* DUMMY BODY */ }

void MovementSystem::update(Ogre::Real delta)
{
	last_delta_ = delta;
	for(auto& ent : entities_.get_component_container<PathfindingComponent>())
	{
		auto& path_comp = ent.second;

		if(path_comp.path_queue.empty())
			continue;

		auto move_comp = entities_.get_component<MovementComponent>(ent.first);
		auto phys_comp = entities_.get_component<PhysicsComponent>(ent.first);
		if(!move_comp || !phys_comp)
			continue;

		auto next = path_comp.path_queue.front();
		auto dir_to_next = MovementHelper::dir_to(entities_, ent.first, next);
		dir_to_next.y = REAL_ZERO; // Will prohibit the entity from going under the ground.
		dir_to_next.normalise();

		if(!move(ent.first, dir_to_next))
		{
			// TODO: Perform a*? Or wait and then perform a*?
		}

		auto pos_next = PhysicsHelper::get_position(entities_, next);
		pos_next.y = phys_comp->half_height; // Ignore the Y distance.
		if(pos_next.distance(phys_comp->position) < move_comp->speed_modifier * delta)
		{
			PhysicsHelper::move_to(entities_, ent.first, pos_next);
			path_comp.last_id = next;
			path_comp.path_queue.pop_front();
			if(!path_comp.path_queue.empty())
				GraphicsHelper::look_at(entities_, ent.first, path_comp.path_queue.front());
		}
	}
}

bool MovementSystem::can_move_to(std::size_t id, Ogre::Vector3 pos)
{
	auto graph_comp = entities_.get_component<GraphicsComponent>(id);
	auto phys_comp = entities_.get_component<PhysicsComponent>(id);
	if(!graph_comp)
		return true; // Invisible objects will be able to move anywhere.

	if(phys_comp)
	{

		if(!phys_comp->solid)
			return true;

		graph_comp->node->setPosition(pos); // Old position backed up in phys_comp.position.
		auto& ents = entities_.get_component_container<PhysicsComponent>(); // Only need to check entities with PhysicsComponent.
		for(const auto& ent : ents)
		{
			if(id == ent.first)
				continue;

			if(PhysicsHelper::is_solid(entities_, ent.first) &&
			   GraphicsHelper::collide(entities_, id, ent.first))
			{
				graph_comp->node->setPosition(phys_comp->position);
				return false;
			}
		}

		// Reverts the change, because of possible checks without actual movement.
		graph_comp->node->setPosition(phys_comp->position);
		return true;
	}
	else
		return false;
}

bool MovementSystem::checked_move(std::size_t id, Ogre::Vector3 dir_vector)
{
	auto phys_comp = entities_.get_component<PhysicsComponent>(id);
	auto mov_comp = entities_.get_component<MovementComponent>(id);
	if(phys_comp && mov_comp)
	{
		auto new_pos = phys_comp->position;
		auto dir = dir_vector * mov_comp->speed_modifier; 
		new_pos += dir;

		if(can_move_to(id, new_pos))
		{
			phys_comp->position = new_pos;

			auto graph_comp = entities_.get_component<GraphicsComponent>(id);
			if(graph_comp)
				graph_comp->node->setPosition(phys_comp->position);

			return true;
		}
	}

	return false;
}

bool MovementSystem::move(std::size_t id, Ogre::Vector3 dir_vector)
{
	auto phys_comp = entities_.get_component<PhysicsComponent>(id);
	auto mov_comp = entities_.get_component<MovementComponent>(id);
	if(phys_comp && mov_comp)
	{
		auto new_pos = phys_comp->position;
		auto dir = dir_vector * mov_comp->speed_modifier * last_delta_; 
		new_pos += dir;
		phys_comp->position = new_pos;

		auto graph_comp = entities_.get_component<GraphicsComponent>(id);
		if(graph_comp)
			graph_comp->node->setPosition(phys_comp->position);

		return true;
	}

	return false;
}