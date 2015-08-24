#include "AIHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"


void AIHelper::set_blueprint(EntitySystem& ents, std::size_t id, const std::string& val)
{
	auto comp = ents.get_component<AIComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string & AIHelper::get_blueprint(EntitySystem& ents, std::size_t id)
{
	static const std::string NO_BLUEPRINT{"ERROR"};

	auto comp = ents.get_component<AIComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return NO_BLUEPRINT;
}

void AIHelper::set_faction(EntitySystem& ents, std::size_t id, FACTION val)
{
	auto comp = ents.get_component<AIComponent>(id);
	if(comp)
		comp->faction = val;
}

FACTION AIHelper::get_faction(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<AIComponent>(id);
	if(comp)
		return comp->faction;
	else
		return FACTION::NEUTRAL;
}

void AIHelper::set_state(EntitySystem& ents, std::size_t id, ENTITY_STATE val)
{
	auto comp = ents.get_component<AIComponent>(id);
	if(comp)
		comp->state = val;
}

ENTITY_STATE AIHelper::get_state(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<AIComponent>(id);
	if(comp)
		return comp->state;
	else
		return ENTITY_STATE::NONE;
}