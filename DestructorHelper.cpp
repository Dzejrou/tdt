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

void DestructorHelper::destroy(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<DestructorComponent>(id);
	if(comp)
		lpp::Script::get_singleton().call<void, std::size_t>(comp->blueprint + "dtor", id);
	util::EntityDestroyer::destroy(ents, id);
}
