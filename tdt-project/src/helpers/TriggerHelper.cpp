#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <lppscript/LppScript.hpp>
#include "TriggerHelper.hpp"

static tdt::cache::TriggerCache cache{Component::NO_ENTITY, nullptr};

void TriggerHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	if(comp)
		comp->blueprint = val;
}

const std::string& TriggerHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void TriggerHelper::set_linked_entity(EntitySystem& ents, tdt::uint id, tdt::uint val)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	if(comp)
		comp->linked_entity = val;
}

tdt::uint TriggerHelper::get_linked_entity(EntitySystem& ents, tdt::uint id)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	if(comp)
		return comp->linked_entity;
	else
		return Component::NO_ENTITY;
}

void TriggerHelper::set_cooldown(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	if(comp)
		comp->cooldown = val;
}

tdt::real TriggerHelper::get_cooldown(EntitySystem& ents, tdt::uint id)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	if(comp)
		return comp->cooldown;
	else
		return tdt::real();
}

void TriggerHelper::trigger(EntitySystem& ents, tdt::uint id, tdt::uint target)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	if(comp)
		lpp::Script::instance().call<void, tdt::uint, tdt::uint>(comp->blueprint + ".trigger", id, target);
}

bool TriggerHelper::can_be_triggered_by(EntitySystem& ents, tdt::uint id, tdt::uint target)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	auto fac1 = ents.get_component<FactionComponent>(id);
	auto fac2 = ents.get_component<FactionComponent>(target);
	if(comp && fac1 && fac2)
	{
		if(fac1->faction == FACTION::NEUTRAL)
			return true;
		else
			return fac1->faction != fac2->faction;
	}
	else
		return false;
}

void TriggerHelper::reset_timer(EntitySystem& ents, tdt::uint id)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	if(comp)
		comp->curr_time = 0.f;
}

void TriggerHelper::set_radius(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	if(comp)
		comp->radius = val;
}

tdt::real TriggerHelper::get_radius(EntitySystem& ents, tdt::uint id)
{
	TriggerComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, TriggerComponent);
	if(comp)
		return comp->radius;
	else
		return tdt::real{};
}
