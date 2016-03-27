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

Ogre::Vector3 MovementHelper::dir_to(EntitySystem& ents, std::size_t id1, std::size_t id2)
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

Ogre::Vector3 MovementHelper::get_dir(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementHelper::get_dir_back(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::UNIT_Z;
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementHelper::get_dir_left(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_X;
	else
		return Ogre::Vector3{0, 0, 0};
}

Ogre::Vector3 MovementHelper::get_dir_right(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<GraphicsComponent>(id);
	if(comp)
		return comp->node->getOrientation() * Ogre::Vector3::UNIT_X;
	else
		return Ogre::Vector3{0, 0, 0};
}

void MovementHelper::set_original_speed(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<MovementComponent>(id);
	if(comp)
		comp->original_speed = val;
}

Ogre::Real MovementHelper::get_original_speed(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<MovementComponent>(id);
	if(comp)
		return comp->original_speed;
	else
		return Ogre::Real{};
}

void MovementHelper::reset_speed(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<MovementComponent>(id);
	if(comp)
		comp->speed_modifier = comp->original_speed;
}
