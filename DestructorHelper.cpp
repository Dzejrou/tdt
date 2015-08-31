#include "DestructorHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void DestructorHelper::set_blueprint(EntitySystem& ents, std::size_t id, const std::string& val)
{
	auto comp = ents.get_component<DestructorComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string & DestructorHelper::get_blueprint(EntitySystem& ents, std::size_t id)
{
	static std::string NO_BLUEPRINT{"ERROR"};

	auto comp = ents.get_component<DestructorComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return NO_BLUEPRINT;
}

void DestructorHelper::destroy(EntitySystem& ents, std::size_t id, bool supress_dtor, std::size_t killer)
{
	auto comp = ents.get_component<DestructorComponent>(id);
	if(comp && !supress_dtor)
		lpp::Script::get_singleton().call<void, std::size_t, std::size_t>(comp->blueprint + ".dtor", id, killer);
	util::EntityDestroyer::destroy(ents, id);
}
