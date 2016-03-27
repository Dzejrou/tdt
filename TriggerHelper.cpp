#include "TriggerHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"

void TriggerHelper::set_blueprint(EntitySystem& ents, std::size_t id, const std::string& val)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string& TriggerHelper::get_blueprint(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void TriggerHelper::set_linked_entity(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	if(comp)
		comp->linked_entity = val;
}

std::size_t TriggerHelper::get_linked_entity(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	if(comp)
		return comp->linked_entity;
	else
		return Component::NO_ENTITY;
}

void TriggerHelper::set_cooldown(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	if(comp)
		comp->cooldown = val;
}

Ogre::Real TriggerHelper::get_cooldown(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return Ogre::Real();
}

void TriggerHelper::trigger(EntitySystem& ents, std::size_t id, std::size_t target)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	if(comp)
		lpp::Script::get_singleton().call<void, std::size_t, std::size_t>(comp->blueprint + ".trigger", id, target);
}

bool TriggerHelper::can_be_triggered_by(EntitySystem& ents, std::size_t id, std::size_t target)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	auto fac1 = ents.get_component<FactionComponent>(id);
	auto fac2 = ents.get_component<FactionComponent>(target);
	if(comp && fac1 && fac2)
	{
		if(fac1->faction == FACTION::NEUTRAL)
			return true;
		else
			return fac1->faction != fac2->faction;
	}
	else
		return false;
}

void TriggerHelper::reset_timer(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	if(comp)
		comp->curr_time = 0.f;
}

void TriggerHelper::set_radius(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	if(comp)
		comp->radius = val;
}

Ogre::Real TriggerHelper::get_radius(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<TriggerComponent>(id);
	if(comp)
		return comp->radius;
	else
		return Ogre::Real{};
}
