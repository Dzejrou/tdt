#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "ExperienceValueHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::ExperienceValueCache cache{Component::NO_ENTITY, nullptr};
#endif

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
