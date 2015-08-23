#include "ProductionHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"

void ProductionHelper::set_production_blueprint(EntitySystem& ents, std::size_t id, const std::string& blueprint)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		comp->product_blueprint = blueprint;
}

const std::string& ProductionHelper::get_production_blueprint(EntitySystem& ents, std::size_t id)
{
	static const std::string NO_BLUEPRINT{"ERROR"};

	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		return comp->product_blueprint;
	else
		return NO_BLUEPRINT;
}

void ProductionHelper::set_production_limit(EntitySystem& ents, std::size_t id, std::size_t limit)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		comp->max_produced = limit;
}

std::size_t ProductionHelper::get_production_limit(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		return comp->max_produced;
	else
		return std::size_t{};
}

void ProductionHelper::set_production_cooldown(EntitySystem& ents, std::size_t id, Ogre::Real cd)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		comp->cooldown = cd;
}

Ogre::Real ProductionHelper::get_production_cooldown(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return Ogre::Real{};
}

void ProductionHelper::set_production_progress(EntitySystem& ents, std::size_t id, Ogre::Real prog)
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

Ogre::Real ProductionHelper::get_production_progress(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		return comp->curr_cd;
	else
		return Ogre::Real();
}

void ProductionHelper::set_production_count(EntitySystem& ents, std::size_t id, std::size_t count)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		comp->curr_produced = count;
}

std::size_t ProductionHelper::get_production_count(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<ProductionComponent>(id);
	if(comp)
		return comp->curr_produced;
	else
		return std::size_t{};
}