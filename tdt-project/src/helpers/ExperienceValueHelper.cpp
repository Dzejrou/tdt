#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "ExperienceValueHelper.hpp"

void ExperienceValueHelper::set(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<ExperienceValueComponent>(id);
	if(comp)
		comp->value = val;
}

tdt::uint ExperienceValueHelper::get(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<ExperienceValueComponent>(id);
	if(comp)
		return comp->value;
	else
		return tdt::uint{};
}

void ExperienceValueHelper::increase(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<ExperienceValueComponent>(id);
	if(comp)
		comp->value += val;
}

void ExperienceValueHelper::decrease(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	auto comp = ents.get_component<ExperienceValueComponent>(id);
	if(comp && comp->value >= val)
		comp->value -= val;
}
