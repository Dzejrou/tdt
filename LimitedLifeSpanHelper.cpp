#include "LimitedLifeSpanHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void LimitedLifeSpanHelper::set_max_time(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<LimitedLifeSpanComponent>(id);
	if(comp)
		comp->max_time = val;
}

Ogre::Real LimitedLifeSpanHelper::get_max_time(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<LimitedLifeSpanComponent>(id);
	if(comp)
		return comp->max_time;
	else
		return Ogre::Real{};
}

Ogre::Real LimitedLifeSpanHelper::get_curr_time(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<LimitedLifeSpanComponent>(id);
	if(comp)
		return comp->curr_time;
	else
		return Ogre::Real{};
}

void LimitedLifeSpanHelper::advance_curr_time(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<LimitedLifeSpanComponent>(id);
	if(comp)
		comp->curr_time += val;
}
