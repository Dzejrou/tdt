#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <lppscript/LppScript.hpp>
#include "ConstructorHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::ConstructorCache cache{Component::NO_ENTITY, nullptr};
#endif

void ConstructorHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	ConstructorComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ConstructorComponent);
	if(comp)
		comp->blueprint = val;
}

const std::string& ConstructorHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	ConstructorComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ConstructorComponent);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void ConstructorHelper::call(EntitySystem& ents, tdt::uint id)
{
	ConstructorComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ConstructorComponent);
	if(comp)
		lpp::Script::instance().call<void, tdt::uint>(comp->blueprint + ".construct", id);
}
