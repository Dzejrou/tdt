#include <numeric>
#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "PhysicsHelper.hpp"

void PhysicsHelper::set_solid(EntitySystem& ents, tdt::uint id, bool val)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		comp->solid = val;
}

bool PhysicsHelper::is_solid(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		return comp->solid;
	else
		return false;
}

void PhysicsHelper::set_position(EntitySystem& ents, tdt::uint id, const Ogre::Vector3& val)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
	{
		comp->position = val;
		auto graph = ents.get_component<GraphicsComponent>(id);
		if(graph && graph->node)
			graph->node->setPosition(val);
	}
}

const Ogre::Vector3& PhysicsHelper::get_position(EntitySystem& ents, tdt::uint id)
{
	static Ogre::Vector3 NO_POSITION{-1.f, -1.f, -1.f};
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		return comp->position;
	else
		return NO_POSITION;
}

void PhysicsHelper::set_half_height(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		comp->half_height = val;
}

tdt::real PhysicsHelper::get_half_height(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		return comp->half_height;
	else
		return tdt::real{};
}

void PhysicsHelper::move_to(EntitySystem& ents, tdt::uint id, Ogre::Vector3 pos)
{
	auto phys_comp = ents.get_component<PhysicsComponent>(id);
	if(phys_comp)
	{
		phys_comp->position = pos;

		auto graph_comp = ents.get_component<GraphicsComponent>(id);
		if(graph_comp)
			graph_comp->node->setPosition(pos);
	}
}

tdt::real PhysicsHelper::get_distance(EntitySystem& ents, tdt::uint id1, tdt::uint id2)
{
	auto comp1 = ents.get_component<PhysicsComponent>(id1);
	auto comp2 = ents.get_component<PhysicsComponent>(id2);
	if(comp1 && comp2)
	{
		auto pos1 = comp1->position;
		auto pos2 = comp2->position;
		pos1.y = pos2.y = 0;
		return pos1.squaredDistance(pos2);
	}
	else
		return std::numeric_limits<tdt::real>::max();
}

tdt::real PhysicsHelper::get_angle(Ogre::Vector3 v1, Ogre::Vector3 v2)
{
	return v1.angleBetween(v2).valueRadians();
}

void PhysicsHelper::set_2d_position(EntitySystem& ents, tdt::uint id, Ogre::Vector2 val)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
	{
		comp->position.x = val.x;
		comp->position.y = comp->half_height;
		comp->position.z = val.y;
		
		auto graph = ents.get_component<GraphicsComponent>(id);
		if(graph)
			graph->node->setPosition(comp->position);
	}
}

Ogre::Vector2 PhysicsHelper::get_2d_position(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		return Ogre::Vector2{comp->position.x, comp->position.z};
	else
		return Ogre::Vector2{};
}
