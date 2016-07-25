#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "MovementHelper.hpp"

tdt::real MovementHelper::get_speed_modifier(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<MovementComponent>(id);
	if(comp)
		return comp->speed_modifier;
	else
		return tdt::real{};
}

void MovementHelper::set_speed_modifier(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<MovementComponent>(id);
	if(comp)
		comp->speed_modifier = val;
}

Ogre::Vector3 MovementHelper::dir_to(EntitySystem& ents, tdt::uint id1, tdt::uint id2)
{
	auto comp1 = ents.get_component<PhysicsComponent>(id1);
	auto comp2 = ents.get_component<PhysicsComponent>(id2);
	if(comp1 && comp2)
	{
		auto pos = comp2->position - comp1->position;
		return pos;
	}
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementHelper::get_dir(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementHelper::get_dir_back(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::UNIT_Z;
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementHelper::get_dir_left(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_X;
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementHelper::get_dir_right(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::UNIT_X;
	else
		return Ogre::Vector3{0, 0, 0};
}

void MovementHelper::set_original_speed(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<MovementComponent>(id);
	if(comp)
		comp->original_speed = val;
}

tdt::real MovementHelper::get_original_speed(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<MovementComponent>(id);
	if(comp)
		return comp->original_speed;
	else
		return tdt::real{};
}

void MovementHelper::reset_speed(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<MovementComponent>(id);
	if(comp)
		comp->speed_modifier = comp->original_speed;
}
