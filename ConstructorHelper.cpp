#include "ConstructorHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"

void ConstructorHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	auto comp = ents.get_component<ConstructorComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string& ConstructorHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<ConstructorComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void ConstructorHelper::call(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<ConstructorComponent>(id);
	if(comp)
		lpp::Script::get_singleton().call<void, tdt::uint>(comp->blueprint + ".construct", id);
}
