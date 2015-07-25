#include "AISystem.hpp"

AISystem::AISystem(EntitySystem& ent)
	: entities_{ent}
{ /* DUMMY BODY */ }

void AISystem::update(Ogre::Real)
{
	for(auto& ent : entities_.get_component_container<AIComponent>())
	{
		const std::string& blueprint  = ent.second.blueprint;
		lpp::Script::get_singleton().call<void, std::size_t>(blueprint + ".update", ent.first);
	}
}

bool AISystem::is_valid(std::size_t id) const
{
	return entities_.has_component<AIComponent>(id);
}

bool AISystem::is_friendly(std::size_t id1, std::size_t id2) const
{
	if(is_valid(id1) && is_valid(id2))
	{
		auto& ai1 = entities_.get_component<AIComponent>(id1);
		auto& ai2 = entities_.get_component<AIComponent>(id2);

		if(ai1.faction == Faction::NEUTRAL || ai2.faction == Faction::NEUTRAL)
			return true;
		else
			return ai1.faction == ai2.faction;
	}
	else
		return true; // Entities withou AIComponent are buildings, walls etc.
}

bool AISystem::is_neutral(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<AIComponent>(id).faction == Faction::NEUTRAL;
	else
		return true;
}

bool AISystem::is_inanimate(std::size_t id) const
{
	return !is_valid(id);
}

std::string AISystem::get_blueprint(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<AIComponent>(id).blueprint;
	else
		return "ERROR"; // Special blueprint defined in ogre_utils.lua
}

void AISystem::set_blueprint(std::size_t id, const std::string& blueprint)
{
	if(is_valid(id))
		entities_.get_component<AIComponent>(id).blueprint = blueprint;
}

EntityState AISystem::get_state(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<AIComponent>(id).state;
	else
		return EntityState::NONE;
}

void AISystem::set_state(std::size_t id, EntityState state)
{
	if(is_valid(id))
		entities_.get_component<AIComponent>(id).state = state;
}

Faction AISystem::get_faction(std::size_t id) const
{
	if(is_valid(id))
		return entities_.get_component<AIComponent>(id).faction;
	else
		return Faction::NEUTRAL;
}

void AISystem::set_faction(std::size_t id, Faction faction)
{
	if(is_valid(id))
		entities_.get_component<AIComponent>(id).faction = faction;
}
