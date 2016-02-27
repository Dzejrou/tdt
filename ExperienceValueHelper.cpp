#include "ExperienceValueHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void ExperienceValueHelper::set(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<ExperienceValueComponent>(id);
	if(comp)
		comp->value = val;
}

std::size_t ExperienceValueHelper::get(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ExperienceValueComponent>(id);
	if(comp)
		return comp->value;
	else
		return std::size_t{};
}

void ExperienceValueHelper::increase(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<ExperienceValueComponent>(id);
	if(comp)
		comp->value += val;
}

void ExperienceValueHelper::decrease(EntitySystem& ents, std::size_t id, std::size_t val)
{
	auto comp = ents.get_component<ExperienceValueComponent>(id);
	if(comp && comp->value >= val)
		comp->value -= val;
}
