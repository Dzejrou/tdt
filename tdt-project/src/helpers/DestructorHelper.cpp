#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <tools/Util.hpp>
#include <lppscript/LppScript.hpp>
#include "DestructorHelper.hpp"

static tdt::cache::DestructorCache cache{Component::NO_ENTITY, nullptr};

void DestructorHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	DestructorComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, DestructorComponent);
	if(comp)
		comp->blueprint = val;
}

const std::string & DestructorHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	DestructorComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, DestructorComponent);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void DestructorHelper::destroy(EntitySystem& ents, tdt::uint id, bool supress_dtor, tdt::uint killer)
{
	DestructorComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, DestructorComponent);
	if(comp && !supress_dtor)
		lpp::Script::instance().call<void, tdt::uint, tdt::uint>(comp->blueprint + ".dtor", id, killer);
	util::EntityDestroyer::destroy(ents, id);
}
