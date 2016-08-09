#include <Components.hpp>
#include <Cache.hpp>
#include <systems/EntitySystem.hpp>
#include <lppscript/LppScript.hpp>
#include "OnHitHelper.hpp"

static tdt::cache::OnHitCache cache{Component::NO_ENTITY, nullptr};

void OnHitHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	OnHitComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, OnHitComponent);
	if(comp)
		comp->blueprint = val;
}

const std::string& OnHitHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	OnHitComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, OnHitComponent);
	if(comp)
		return comp->blueprint;
	else
		return ents.NO_BLUEPRINT;
}

void OnHitHelper::call(EntitySystem& ents, tdt::uint id, tdt::uint hitter)
{
	OnHitComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, OnHitComponent);
	if(comp && comp->curr_time >= comp->cooldown)
	{
		comp->curr_time = 0.f;
		lpp::Script::instance().call<void, tdt::uint, tdt::uint>(comp->blueprint + ".on_hit", id, hitter);
	}
}

void OnHitHelper::set_cooldown(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	OnHitComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, OnHitComponent);
	if(comp)
		comp->cooldown = val;
}

tdt::real OnHitHelper::get_cooldown(EntitySystem& ents, tdt::uint id)
{
	OnHitComponent* comp{nullptr};
	GET_COMPONENT(id, ents, comp, OnHitComponent);
	if(comp)
		return comp->cooldown;
	else
		return tdt::real{};
}
