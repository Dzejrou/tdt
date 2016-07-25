#include <Components.hpp>
#include <systems/EntitySystem.hpp>
#include <lppscript/LppScript.hpp>
#include "OnHitHelper.hpp"

void OnHitHelper::set_blueprint(EntitySystem& ents, tdt::uint id, const std::string& val)
{
	auto comp = ents.get_component<OnHitComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string& OnHitHelper::get_blueprint(EntitySystem& ents, tdt::uint id)
{
	static const std::string NO_BLUEPRINT{"ERROR"};

	auto comp = ents.get_component<OnHitComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return NO_BLUEPRINT;
}

void OnHitHelper::call(EntitySystem& ents, tdt::uint id, tdt::uint hitter)
{
	auto comp = ents.get_component<OnHitComponent>(id);
	if(comp && comp->curr_time >= comp->cooldown)
	{
		comp->curr_time = 0.f;
		lpp::Script::instance().call<void, tdt::uint, tdt::uint>(comp->blueprint + ".on_hit", id, hitter);
	}
}

void OnHitHelper::set_cooldown(EntitySystem& ents, tdt::uint id, tdt::real val)
{
	auto comp = ents.get_component<OnHitComponent>(id);
	if(comp)
		comp->cooldown = val;
}

tdt::real OnHitHelper::get_cooldown(EntitySystem& ents, tdt::uint id)
{
	auto comp = ents.get_component<OnHitComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return tdt::real{};
}
