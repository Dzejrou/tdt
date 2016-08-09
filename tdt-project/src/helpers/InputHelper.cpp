#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "InputHelper.hpp"

static tdt::cache::InputCache cache{Component::NO_ENTITY, nullptr};

void InputHelper::set_input_handler(EntitySystem& ents, tdt::uint id, const std::string& handler)
{
	InputComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, InputComponent);
	if(comp)
		comp->input_handler = handler;
}

const std::string& InputHelper::get_input_handler(EntitySystem& ents, tdt::uint id)
{
	InputComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, InputComponent);
	if(comp)
		return comp->input_handler;
	else
		return ents.NO_BLUEPRINT;
}