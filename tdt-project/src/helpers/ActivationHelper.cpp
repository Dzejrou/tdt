#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <lppscript/LppScript.hpp>
#include "ActivationHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::ActivationCache cache{Component::NO_ENTITY, nullptr};
#endif

void ActivationHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	ActivationComponent* comp;
	GET_COMPONENT(id, ents, comp, ActivationComponent);
	if(comp)
		comp->blueprint = val;
}

const std::string& ActivationHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	ActivationComponent* comp;
	GET_COMPONENT(id, ents, comp, ActivationComponent);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void ActivationHelper::activate(EntitySystem& ents, tdt::uint id)
{
	ActivationComponent* comp;
	GET_COMPONENT(id, ents, comp, ActivationComponent);
	if(comp && !comp->activated)
	{
		comp->activated = true;
		lpp::Script::instance().call<void, tdt::uint>(comp->blueprint + ".activate", id);
	}
}

void ActivationHelper::deactivate(EntitySystem& ents, tdt::uint id)
{
	ActivationComponent* comp;
	GET_COMPONENT(id, ents, comp, ActivationComponent);
	if(comp && comp->activated)
	{
		comp->activated = false;
		lpp::Script::instance().call<void, tdt::uint>(comp->blueprint + ".deactivate", id);
	}
}

bool ActivationHelper::is_activated(EntitySystem& ents, tdt::uint id)
{
	ActivationComponent* comp;
	GET_COMPONENT(id, ents, comp, ActivationComponent);
	if(comp)
		return comp->activated;
	else
		return false;
}
