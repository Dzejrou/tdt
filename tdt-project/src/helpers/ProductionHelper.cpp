#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include "ProductionHelper.hpp"

static tdt::cache::ProductionCache cache{Component::NO_ENTITY, nullptr};

void ProductionHelper::set_production_blueprint(EntitySystem& ents, tdt::uint id, const std::string& blueprint)
{
	ProductionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductionComponent);
	if(comp)
		comp->product_blueprint = blueprint;
}

const std::string& ProductionHelper::get_production_blueprint(EntitySystem& ents, tdt::uint id)
{
	ProductionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductionComponent);
	if(comp)
		return comp->product_blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void ProductionHelper::set_production_limit(EntitySystem& ents, tdt::uint id, tdt::uint limit)
{
	ProductionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductionComponent);
	if(comp)
		comp->max_produced = limit;
}

tdt::uint ProductionHelper::get_production_limit(EntitySystem& ents, tdt::uint id)
{
	ProductionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductionComponent);
	if(comp)
		return comp->max_produced;
	else
		return tdt::uint{};
}

void ProductionHelper::set_production_cooldown(EntitySystem& ents, tdt::uint id, tdt::real cd)
{
	ProductionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductionComponent);
	if(comp)
		comp->cooldown = cd;
}

tdt::real ProductionHelper::get_production_cooldown(EntitySystem& ents, tdt::uint id)
{
	ProductionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductionComponent);
	if(comp)
		return comp->cooldown;
	else
		return tdt::real{};
}

void ProductionHelper::set_production_progress(EntitySystem& ents, tdt::uint id, tdt::real prog)
{
	ProductionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductionComponent);
	if(comp)
	{
		if(prog < comp->cooldown)
			comp->curr_cd = prog;
		else
			comp->curr_cd = comp->cooldown;
	}
}

tdt::real ProductionHelper::get_production_progress(EntitySystem& ents, tdt::uint id)
{
	ProductionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductionComponent);
	if(comp)
		return comp->curr_cd;
	else
		return tdt::real();
}

void ProductionHelper::set_production_count(EntitySystem& ents, tdt::uint id, tdt::uint count)
{
	ProductionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductionComponent);
	if(comp)
		comp->curr_produced = count;
}

tdt::uint ProductionHelper::get_production_count(EntitySystem& ents, tdt::uint id)
{
	ProductionComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, ProductionComponent);
	if(comp)
		return comp->curr_produced;
	else
		return tdt::uint{};
}