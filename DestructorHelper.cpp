#include "DestructorHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "Util.hpp"
#include "lppscript/LppScript.hpp"

void DestructorHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	auto comp = ents.get_component<DestructorComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string & DestructorHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	static std::string NO_BLUEPRINT{"ERROR"};

	auto comp = ents.get_component<DestructorComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return NO_BLUEPRINT;
}

void DestructorHelper::destroy(EntitySystem& ents, tdt::uint id, bool supress_dtor, tdt::uint killer)
{
	auto comp = ents.get_component<DestructorComponent>(id);
	if(comp && !supress_dtor)
		lpp::Script::instance().call<void, tdt::uint, tdt::uint>(comp->blueprint + ".dtor", id, killer);
	util::EntityDestroyer::destroy(ents, id);
}
