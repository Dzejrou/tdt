#include "MovementSystem.hpp"

MovementSystem::MovementSystem(EntitySystem& ents)
	: entities_{ents}
{ /* DUMMY BODY */ }

void MovementSystem::update(Ogre::Real delta)
{ // TODO: Fix this...
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
		auto dir_to_next = dir_to_enemy(ent.first, next); // TODO: Rename to dir_to_entity?
		dir_to_next.y = 0; // Will prohibit the entity from going under the ground.
		dir_to_next.normalise();

		if(!move(ent.first, dir_to_next))
		{
			// TODO: perform a*? Or wait and then perform a*?
		}

		auto pos_next = PhysicsHelper::get_position(entities_, next);
		pos_next.y = phys_comp->half_height; // Ignore the Y distance.
		if(pos_next.distance(phys_comp->position) < move_comp->speed_modifier)
		{
			move_to(ent.first, pos_next);
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

bool MovementSystem::move(std::size_t id, Ogre::Vector3 dir_vector)
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

std::size_t MovementSystem::enemy_in_radius(std::size_t id, Ogre::Real radius) const
{
	auto comp = entities_.get_component<PhysicsComponent>(id);
	if(comp)
	{
		radius *= radius; // Using squared distance.
		Ogre::Real minimum_distance{std::numeric_limits<Ogre::Real>::max()};
		std::size_t minimum_id{id};
		std::size_t original_id{id};
		Ogre::Real current_distance{};

		for(const auto& ent : entities_.get_component_container<PhysicsComponent>())
		{
			if(ent.first == original_id)
				continue;
			current_distance = comp->position.squaredDistance(ent.second.position);
			if((current_distance < radius || radius == std::numeric_limits<Ogre::Real>::max()) &&
			   current_distance < minimum_distance)
			{
				minimum_distance = current_distance;
				id = ent.first;
			}
		}
	}

	return id; // Return the calling ID if no close entity found.
}

std::size_t MovementSystem::closest_enemy(std::size_t id) const
{
	return enemy_in_radius(id, std::numeric_limits<Ogre::Real>::max());
}

Ogre::Vector3 MovementSystem::dir_to_closest_enemy(std::size_t id, Ogre::Real radius) const
{
	auto comp = entities_.get_component<PhysicsComponent>(id);
	if(comp)
	{
		std::size_t id_enemy = enemy_in_radius(id, radius);
		if(id == id_enemy)
			return Ogre::Vector3{0, 0, 0};
		auto pos_enemy = entities_.get_component<PhysicsComponent>(id_enemy)->position;
		auto pos = pos_enemy - comp->position;
		return pos;
	}
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementSystem::dir_to_enemy(std::size_t id1, std::size_t id2) const
{
	auto comp1 = entities_.get_component<PhysicsComponent>(id1);
	auto comp2 = entities_.get_component<PhysicsComponent>(id2);
	if(comp1 && comp2)
	{
		auto pos = comp2->position - comp1->position;
		return pos;
	}
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementSystem::get_dir(std::size_t id) const
{
	auto comp = entities_.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementSystem::get_dir_back(std::size_t id) const
{
	auto comp = entities_.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::UNIT_Z;
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementSystem::get_dir_left(std::size_t id) const
{
	auto comp = entities_.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_X;
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementSystem::get_dir_right(std::size_t id) const
{
	auto comp = entities_.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::UNIT_X;
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Real MovementSystem::get_angle(Ogre::Vector3 v1, Ogre::Vector3 v2) const
{
	return v1.angleBetween(v2).valueRadians();
}

void MovementSystem::set_solid(std::size_t id, bool solid)
{
	auto comp = entities_.get_component<PhysicsComponent>(id);
	if(comp)
		comp->solid = solid;
}

void MovementSystem::set_half_height(std::size_t id, Ogre::Real hh)
{
	auto comp = entities_.get_component<PhysicsComponent>(id);
	if(comp)
		comp->half_height = hh;
}