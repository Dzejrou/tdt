#include "SpellHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"

void SpellHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	auto comp = ents.get_component<SpellComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string& SpellHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<SpellComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void SpellHelper::set_cooldown(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<SpellComponent>(id);
	if(comp)
		comp->cooldown = val;
}

tdt::real SpellHelper::get_cooldown(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<SpellComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return tdt::real{};
}

void SpellHelper::advance_curr_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<SpellComponent>(id);
	if(comp)
		comp->cd_time += val;
}

void SpellHelper::set_curr_time(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<SpellComponent>(id);
	if(comp)
		comp->cd_time = val;
}

tdt::real SpellHelper::get_curr_time(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<SpellComponent>(id);
	if(comp)
		return comp->cd_time;
	else
		return tdt::real{};
}

void SpellHelper::cast(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<SpellComponent>(id);
	if(comp)
		lpp::Script::instance().call<void, tdt::uint>(comp->blueprint + ".cast", id);
}
