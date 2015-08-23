#include "PhysicsHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void PhysicsHelper::set_solid(EntitySystem& ents, std::size_t id, bool val)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		comp->solid = val;
}

bool PhysicsHelper::is_solid(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		return comp->solid;
	else
		return false;
}

void PhysicsHelper::set_position(EntitySystem& ents, std::size_t id, const Ogre::Vector3& val)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		comp->position = val;
}

const Ogre::Vector3& PhysicsHelper::get_position(EntitySystem& ents, std::size_t id)
{
	static Ogre::Vector3 NO_POSITION{0.f, 100.f, 0.f};
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		return comp->position;
	else
		return NO_POSITION;
}

void PhysicsHelper::set_halfheight(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		comp->half_height = val;
}

Ogre::Real PhysicsHelper::get_halfheight(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<PhysicsComponent>(id);
	if(comp)
		return comp->half_height;
	else
		return Ogre::Real{};
}