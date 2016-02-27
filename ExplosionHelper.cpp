#include "ExplosionHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void ExplosionHelper::set_delta(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		comp->delta = val;
}

Ogre::Real ExplosionHelper::get_delta(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		return comp->delta;
	else
		return Ogre::Real{};
}

void ExplosionHelper::set_max_radius(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		comp->max_radius = val;
}

Ogre::Real ExplosionHelper::get_max_radius(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		return comp->max_radius;
	else
		return Ogre::Real{};
}

Ogre::Real ExplosionHelper::get_curr_radius(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		return comp->curr_radius;
	else
		return Ogre::Real{};
}

void ExplosionHelper::increase_curr_radius(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<ExplosionComponent>(id);
	if(comp)
		comp->curr_radius += val;
}
