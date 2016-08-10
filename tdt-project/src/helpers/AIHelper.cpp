#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "AIHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::AICache cache{Component::NO_ENTITY, nullptr};
#endif

void AIHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	AIComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AIComponent);
	if(comp)
		comp->blueprint = val;
}

const std::string & AIHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	AIComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AIComponent);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void AIHelper::set_state(EntitySystem& ents, tdt::uint id, ENTITY_STATE::VAL val)
{
	AIComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AIComponent);
	if(comp)
		comp->state = val;
}

ENTITY_STATE::VAL AIHelper::get_state(EntitySystem& ents, tdt::uint id)
{
	AIComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, AIComponent);
	if(comp)
		return comp->state;
	else
		return ENTITY_STATE::NONE;
}
