#include "ConstructorHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"

void ConstructorHelper::set_blueprint(EntitySystem& ents, std::size_t id, const std::string& val)
{
	auto comp = ents.get_component<ConstructorComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string& ConstructorHelper::get_blueprint(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ConstructorComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void ConstructorHelper::call(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ConstructorComponent>(id);
	if(comp)
		lpp::Script::get_singleton().call<void, std::size_t>(comp->blueprint + ".construct", id);
}
