#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "AIHelper.hpp"

void AIHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	auto comp = ents.get_component<AIComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string & AIHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	static const std::string NO_BLUEPRINT{"ERROR"};

	auto comp = ents.get_component<AIComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return NO_BLUEPRINT;
}

void AIHelper::set_state(EntitySystem& ents, tdt::uint id, ENTITY_STATE::VAL val)
{
	auto comp = ents.get_component<AIComponent>(id);
	if(comp)
		comp->state = val;
}

ENTITY_STATE::VAL AIHelper::get_state(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<AIComponent>(id);
	if(comp)
		return comp->state;
	else
		return ENTITY_STATE::NONE;
}
