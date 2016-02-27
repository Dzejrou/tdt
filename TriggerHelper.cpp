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
