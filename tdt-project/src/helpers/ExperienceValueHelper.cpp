#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "ExperienceValueHelper.hpp"

static tdt::cache::ExperienceValueCache cache{Component::NO_ENTITY, nullptr};

void ExperienceValueHelper::set(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	ExperienceValueComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ExperienceValueComponent);
	if(comp)
		comp->value = val;
}

tdt::uint ExperienceValueHelper::get(EntitySystem& ents, tdt::uint id)
{
	ExperienceValueComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ExperienceValueComponent);
	if(comp)
		return comp->value;
	else
		return tdt::uint{};
}

void ExperienceValueHelper::increase(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	ExperienceValueComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ExperienceValueComponent);
	if(comp)
		comp->value += val;
}

void ExperienceValueHelper::decrease(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	ExperienceValueComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ExperienceValueComponent);
	if(comp && comp->value >= val)
		comp->value -= val;
}
