#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include "ProductionHelper.hpp"

void ProductionHelper::set_production_blueprint(EntitySystem& ents, tdt::uint id, const std::string& blueprint)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		comp->product_blueprint = blueprint;
}

const std::string& ProductionHelper::get_production_blueprint(EntitySystem& ents, tdt::uint id)
{
	static const std::string NO_BLUEPRINT{"ERROR"};

	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		return comp->product_blueprint;
	else
		return NO_BLUEPRINT;
}

void ProductionHelper::set_production_limit(EntitySystem& ents, tdt::uint id, tdt::uint limit)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		comp->max_produced = limit;
}

tdt::uint ProductionHelper::get_production_limit(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		return comp->max_produced;
	else
		return tdt::uint{};
}

void ProductionHelper::set_production_cooldown(EntitySystem& ents, tdt::uint id, tdt::real cd)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		comp->cooldown = cd;
}

tdt::real ProductionHelper::get_production_cooldown(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return tdt::real{};
}

void ProductionHelper::set_production_progress(EntitySystem& ents, tdt::uint id, tdt::real prog)
{
	auto comp = ents.get_component<ProductionComponent>(id);
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
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		return comp->curr_cd;
	else
		return tdt::real();
}

void ProductionHelper::set_production_count(EntitySystem& ents, tdt::uint id, tdt::uint count)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		comp->curr_produced = count;
}

tdt::uint ProductionHelper::get_production_count(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		return comp->curr_produced;
	else
		return tdt::uint{};
}