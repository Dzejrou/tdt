#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <lppscript/LppScript.hpp>
#include "SpellHelper.hpp"

#if CACHE_ALLOWED == 1
static tdt::cache::SpellCache cache{Component::NO_ENTITY, nullptr};
#endif

void SpellHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	SpellComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SpellComponent);
	if(comp)
		comp->blueprint = val;
}

const std::string& SpellHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	SpellComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SpellComponent);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void SpellHelper::set_cooldown(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	SpellComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SpellComponent);
	if(comp)
		comp->cooldown = val;
}

tdt::real SpellHelper::get_cooldown(EntitySystem& ents, tdt::uint id)
{
	SpellComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SpellComponent);
	if(comp)
		return comp->cooldown;
	else
		return tdt::real{};
}

void SpellHelper::advance_curr_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	SpellComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SpellComponent);
	if(comp)
		comp->cd_time += val;
}

void SpellHelper::set_curr_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	SpellComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SpellComponent);
	if(comp)
		comp->cd_time = val;
}

tdt::real SpellHelper::get_curr_time(EntitySystem& ents, tdt::uint id)
{
	SpellComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SpellComponent);
	if(comp)
		return comp->cd_time;
	else
		return tdt::real{};
}

void SpellHelper::cast(EntitySystem& ents, tdt::uint id)
{
	SpellComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, SpellComponent);
	if(comp)
		lpp::Script::instance().call<void, tdt::uint>(comp->blueprint + ".cast", id);
}
