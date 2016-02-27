#include "OnHitHelper.hpp"
#include "Components.hpp"
#include "EntitySystem.hpp"
#include "lppscript/LppScript.hpp"

void OnHitHelper::set_blueprint(EntitySystem& ents, std::size_t id, const std::string& val)
{
	auto comp = ents.get_component<OnHitComponent>(id);
	if(comp)
		comp->blueprint = val;
}

const std::string& OnHitHelper::get_blueprint(EntitySystem& ents, std::size_t id)
{
	static const std::string NO_BLUEPRINT{"ERROR"};

	auto comp = ents.get_component<OnHitComponent>(id);
	if(comp)
		return comp->blueprint;
	else
		return NO_BLUEPRINT;
}

void OnHitHelper::call(EntitySystem& ents, std::size_t id, std::size_t hitter)
{
	auto comp = ents.get_component<OnHitComponent>(id);
	if(comp && comp->curr_time >= comp->cooldown)
	{
		comp->curr_time = 0.f;
		lpp::Script::get_singleton().call<void, std::size_t, std::size_t>(comp->blueprint + ".on_hit", id, hitter);
	}
}

void OnHitHelper::set_cooldown(EntitySystem& ents, std::size_t id, Ogre::Real val)
{
	auto comp = ents.get_component<OnHitComponent>(id);
	if(comp)
		comp->cooldown = val;
}

Ogre::Real OnHitHelper::get_cooldown(EntitySystem& ents, std::size_t id)
{
	auto comp = ents.get_component<OnHitComponent>(id);
	if(comp)
		return comp->cooldown;
	else
		return Ogre::Real{};
}
